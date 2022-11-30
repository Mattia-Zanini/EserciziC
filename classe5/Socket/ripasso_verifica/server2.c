#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define DIM 512
#define PORT 1024

#define TRUE 1
#define FALSE 0

typedef struct
{
    char nome[DIM];
    double altezza;
} data_t;

int main()
{
    struct sockaddr_in server, client;
    int socketfd, alto, structLen = sizeof(client);
    data_t info;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(socketfd, (struct sockaddr *)&server, structLen);
    listen(socketfd, 3);

    while (TRUE)
    {
        int acceptfd;
        printf("Server in ascolto...\n");
        acceptfd = accept(socketfd, (struct sockaddr *)&server, (socklen_t *)&structLen);
        recv(acceptfd, &info, sizeof(info), 0);

        if (info.altezza > 1.75)
            alto = 1;
        else
            alto = 0;
        send(acceptfd, &alto, sizeof(alto), 0);
        close(acceptfd);
    }
}