#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DIM 512
#define SERVERPORT 1313

int main()
{
    struct sockaddr_in servizio, addr_remoto; // record con i dati del server e del client
    int socketfd, soa, fromlen = sizeof(servizio);
    char str[DIM];

    // definizione dei dati del socket
    servizio.sin_family = AF_INET; // AF_INET --> IPv4
    // servizio.sin_addr.s_addr = INADDR_ANY;
    servizio.sin_addr.s_addr = htonl(INADDR_ANY);
    // servizio.sin_addr.s_addr = inet_addr("127.0.0.1");
    servizio.sin_port = htons(SERVERPORT);

    // impostazione del transport endpoint del server
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    // leghiamo l'indirizzo al transport endpoint
    bind(socketfd, (struct sockaddr *)&servizio, sizeof(servizio));

    // poniamo il server in ascolto delle richieste dei client
    listen(socketfd, 10); // può attendere fino a 10 client

    // ciclo infinito
    while (1)
    {
        printf("\nServer in ascolto...");

        fflush(stdout);

        soa = accept(socketfd, (struct sockaddr *)&addr_remoto, (socklen_t *)&fromlen);
        // legge dal client
        read(soa, str, sizeof(str));

        printf("Stringa ricevuta: %s\nIp Client: %s\n", str, inet_ntoa(addr_remoto.sin_addr));

        close(soa);

        if (strcmp(str, "close") == 0)
            break;
    }

    return 0;
}