#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define DIM 1024
#define SERVERPORT 49153

#define MAX_TIME_RETRY 6.0

int main()
{
    struct sockaddr_in server_remote;
    int socketfd, newPort, stat;
    char buff[DIM] = {0};

    server_remote.sin_family = AF_INET;
    server_remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_remote.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    stat = connect(socketfd, (struct sockaddr *)&server_remote, sizeof(server_remote));
    if (stat < 0)
    {
        printf("Il server al momento non è raggiungibile\n");
        exit(EXIT_FAILURE);
    }

    read(socketfd, buff, DIM);
    printf("Nuova porta: %d\n", atoi(buff));
    close(socketfd);

    newPort = atoi(buff);
    // sleep(1);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    server_remote.sin_port = htons(newPort);

    clock_t t;
    t = clock();

    while (1) // prova a connettersi in contiuazione finchè stat non è uguale a 0 (connessione riuscita)
    {
        stat = connect(socketfd, (struct sockaddr *)&server_remote, sizeof(server_remote));
        // printf("Stato connessione %d\n", stat);
        if ((((double)(clock() - t)) / CLOCKS_PER_SEC) > MAX_TIME_RETRY) // controlla che non impieghi troppo tempo per instaurare la connessione
        {
            printf("Tempo scaduto\n");
            close(socketfd);
            exit(EXIT_FAILURE);
        }
        if (stat == -1) // connessione non andata a buon fine
        {
            close(socketfd);
            socketfd = socket(AF_INET, SOCK_STREAM, 0);
        }
        else // esce dal loop quando la connessione è riuscita
            break;
    }
    /*
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Connessione riuscita dopo %f secondi\n", time_taken);
    */

    printf("Stato connessione %d\n", stat);

    printf("Inserisci la stringa\n");
    scanf("%s", buff);
    write(socketfd, buff, DIM);

    close(socketfd);
    return 0;
}