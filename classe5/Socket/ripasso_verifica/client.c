#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define BUFF_DIM 512
#define PORT 1024

int main()
{
    struct sockaddr_in server;
    int socketfd, risposta;
    char buff[BUFF_DIM] = {0};

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(socketfd, (struct sockaddr *)&server, sizeof(server));

    printf("Inserisci una parola a piacere\n");
    scanf("%s", buff);
    send(socketfd, buff, BUFF_DIM, 0);

    recv(socketfd, &risposta, sizeof(risposta), 0);
    close(socketfd);

    if (risposta == 0)
        printf("La parola non è palindroma\n");
    else
        printf("La parola è palindroma\n");

    int stringLen = strlen(buff) + 1;
    int added = 0;
    char string[stringLen];

    for (int i = 0; i < stringLen; i++)
        string[i] = '\0';

    printf("lunghezza: %ld, added: %d\n", strlen(string), added);
    for (int i = 0; i < strlen(buff); i++)
    {
        int same = 0;
        for (int j = 0; j < strlen(string); j++)
        {
            if (buff[i] == string[j])
                same = 1;
        }
        if (same == 0)
        {
            string[added] = buff[i];
            added++;
        }
    }
    printf("lunghezza: %ld, added: %d\n", strlen(string), added);
    string[added] = '\0';
    printf("Parola senza doppie: %s\n", string);
}