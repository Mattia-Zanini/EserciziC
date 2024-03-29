#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DIM 512
#define SERVERPORT 1313

int main(int argc, char **argv)
{
    struct sockaddr_in servizio;
    int socketfd;
    char str1[DIM];

    servizio.sin_family = AF_INET;
    // servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    servizio.sin_addr.s_addr = inet_addr("127.0.0.1");
    servizio.sin_port = htons(SERVERPORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    connect(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    printf("Inserisci la stringa\n");
    scanf("%s", str1);
    write(socketfd, str1, sizeof(str1));

    close(socketfd);

    return 0;
}