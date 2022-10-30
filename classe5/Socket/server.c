#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_DIM 1024
#define SERVERPORT 1313

#define TRUE 1
#define FALSE 0

void ClearBuffer(char buffer[])
{
    for (int i = 0; i < BUFFER_DIM; i++)
        buffer[i] = 0;
}

int main()
{
    struct sockaddr_in server, client_remote;
    int socketfd, conn, client_len = sizeof(client_remote), childs_port = SERVERPORT;
    char buff[BUFFER_DIM];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&server, sizeof(server));
    listen(socketfd, 1);

    while (TRUE)
    {
        printf("Server Padre in ascolto\n");
        fflush(stdout);

        conn = accept(socketfd, (struct sockaddr *)&client_remote, (socklen_t *)&client_len);
        printf("Connessione Accettata dal padre [IP: %s]\n", inet_ntoa(client_remote.sin_addr));

        childs_port++;

        sprintf(buff, "%d", childs_port);
        printf("Nuova porta del server: %s\n", buff);
        send(conn, buff, sizeof(buff), 0);
        close(conn);
        ClearBuffer(buff);

        int child = fork();
        if (child < 0) // fork failed.
            continue;
        else if (child > 0) // parent process
        {
            // printf("Parent process\n");
            // wait(&child);
        }
        else if (child == 0) // child process
        {
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(childs_port);

            socketfd = socket(AF_INET, SOCK_STREAM, 0);
            bind(socketfd, (struct sockaddr *)&server, sizeof(server));
            listen(socketfd, 1);

            printf("Figlio (%d) in ascolto\n", getpid());
            fflush(stdout);

            conn = accept(socketfd, (struct sockaddr *)&client_remote, (socklen_t *)&client_len);
            printf("Connessione Accettata dal figlio (%d) [PORT: %d]\n", getpid(), childs_port);
            read(conn, buff, sizeof(buff));

            printf("Stringa ricevuta dal figlio (%d) [PORT: %d]: %s\n", getpid(), childs_port, buff);
            close(conn);
            exit(0);
        }
    }
    return 0;
}