#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <error.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_DIM 1024
#define SERVERPORT 49152

#define TRUE 1
#define FALSE 0

#define PIPE_READ 0
#define PIPE_WRITE 1

#define EXIT_SIGINT 2

typedef struct
{
    int sockFD;
    int bindStatus;
    int listenStatus;
    int s_port;
} socket_status_t;

void gestione_segnale(int numero_segnale)
{
    // printf("Ho catturato il segnale SIGINT (CTRL+C, numero segnale %d)!\n", numero_segnale);
    printf("\nChiusura Server...\n");
    exit(EXIT_SIGINT);
}

void ClearBuffer(char buffer[])
{
    for (int i = 0; i < BUFFER_DIM; i++)
        buffer[i] = 0;
}

socket_status_t BindSocket(int addr, int *port, int nClients)
{
    socket_status_t sock_stat;
    struct sockaddr_in sock;
    int len = sizeof(sock);

    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = addr;
    sock.sin_port = htons(*port);

    if ((sock_stat.sockFD = socket(AF_INET, SOCK_STREAM, 0)) < 3)
        perror("socket");
    while (TRUE)
    {
        if ((sock_stat.bindStatus = bind(sock_stat.sockFD, (struct sockaddr *)&sock, len)) == -1)
        {
            perror("bind");
            if ((sock_stat.sockFD = socket(AF_INET, SOCK_STREAM, 0)) < 3)
                perror("socket");
            (*port)++;
            if (*port > 65535)
                (*port) = 49152;
            sock.sin_port = htons(*port);
        }
        else
            break;
    }
    sock_stat.s_port = *port;

    if ((sock_stat.listenStatus = listen(sock_stat.sockFD, nClients)) != 0)
        perror("listen");

    /*
    printf("bind error %d\n", sock_stat.bindStatus);

    if (getsockname(sock_stat.sockFD, (struct sockaddr *)&sock, &len) == -1)
        perror("getsockname");
    */

    printf("port number %d\n", sock_stat.s_port);

    return sock_stat;
}

int main()
{
    struct sockaddr_in socketStruct;
    int socketfd, conn, child, server_port = SERVERPORT, client_len = sizeof(socketStruct);
    char buff[BUFFER_DIM] = {0};

    signal(SIGINT, gestione_segnale);

    socketfd = BindSocket(INADDR_ANY, &server_port, 1).sockFD;
    printf("File descriptor socket: %d\n", socketfd);

    while (TRUE)
    {
        printf("Server in ascolto\n");
        fflush(stdout);

        conn = accept(socketfd, (struct sockaddr *)&socketStruct, (socklen_t *)&client_len);
        printf("Connessione Accettata dal server [IP: %s]\n", inet_ntoa(socketStruct.sin_addr));

        int fd[2];
        int pipeStatus = pipe(fd);
        if (pipeStatus == 0)
        {
            child = fork();
            if (child < 0) // fork failed.
            {
                perror("fork");
                close(fd[PIPE_READ]);
                close(fd[PIPE_WRITE]);
                continue;
            }
            else if (child > 0) // parent process
            {
                // printf("Parent process\n");
                // wait(&child);

                close(fd[PIPE_WRITE]);
                read(fd[PIPE_READ], &server_port, sizeof(server_port));
                close(fd[PIPE_READ]);

                sprintf(buff, "%d", server_port);
                printf("Nuova porta per il client: %s\n", buff);
                send(conn, buff, BUFFER_DIM, 0);
                close(conn);
                ClearBuffer(buff);
            }
            else if (child == 0) // child process
            {
                close(fd[PIPE_READ]);

                socketfd = BindSocket(INADDR_ANY, &server_port, 1).sockFD;

                write(fd[PIPE_WRITE], &server_port, sizeof(server_port));
                close(fd[PIPE_WRITE]);

                printf("Figlio (%d) in ascolto\n", getpid());
                fflush(stdout);

                conn = accept(socketfd, (struct sockaddr *)&socketStruct, (socklen_t *)&client_len);
                printf("Connessione Accettata dal figlio (%d) [PORT: %d]\n", getpid(), server_port);
                read(conn, buff, BUFFER_DIM);

                printf("Stringa ricevuta dal figlio (%d) [PORT: %d]: %s\n", getpid(), server_port, buff);
                close(conn);
                exit(EXIT_SUCCESS);
            }
        }
    }
    return 0;
}