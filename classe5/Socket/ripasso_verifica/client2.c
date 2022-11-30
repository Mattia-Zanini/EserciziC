#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define DIM 512
#define PORT 1024

typedef struct
{
    char nome[DIM];
    double altezza;
} data_t;

int main()
{
    struct sockaddr_in server;
    int socketfd, risposta;
    data_t dato;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&server, sizeof(server));

    printf("Inserisci un nome\n");
    scanf("%s", dato.nome);
    printf("Inserisci l'altezza di %s\n", dato.nome);
    scanf("%lf", &dato.altezza);

    send(socketfd, &dato, sizeof(dato), 0);

    recv(socketfd, &risposta, sizeof(risposta), 0);
    close(socketfd);

    if (risposta == 0)
        printf("%s è un nano\n", dato.nome);
    else
        printf("%s è alto\n", dato.nome);
}