#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define BUFF_DIM 512
#define PORT 1024

#define TRUE 1
#define FALSE 0

int isPalindroma(char *parola)
{
    int parolaLen = strlen(parola);
    char palind[parolaLen + 1];
    for (int i = 0; i < parolaLen; i++)
    {
        printf("[%d]: %c\n", i, parola[parolaLen - 1 - i]);
        palind[i] = parola[parolaLen - 1 - i];
    }

    palind[parolaLen] = '\0';
    int uguale = FALSE;
    if (strcmp(parola, palind) == 0)
        uguale = TRUE;

    printf("Parola al contrario: %s\n", palind);
    printf("Parola originale: %s\n", parola);

    return uguale;
}

int main()
{
    struct sockaddr_in server, client;
    int socketfd, palindroma, structLen = sizeof(client);
    char buff[BUFF_DIM];

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
        recv(acceptfd, buff, BUFF_DIM, 0);
        palindroma = isPalindroma(buff);
        send(acceptfd, &palindroma, sizeof(palindroma), 0);
        close(acceptfd);
    }
}