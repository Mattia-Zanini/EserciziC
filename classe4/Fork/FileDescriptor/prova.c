#include <fcntl.h> //per i flag
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h> //per eseguire le fork

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        exit(-1);
    }

    int numero;
    int p1p2[2];
    pipe(p1p2);

    int pid = fork();
    if (pid == 0)
    {
        printf("Inserisci un numero\n");
        scanf("%d", &numero); // la scanf vuole il formato di quello che riceve in input,
                              // il puntatore della variabile dove deve salvare(&) e il
                              // nome della variabile dove salva ciò che ha preso in input
        close(p1p2[READ]);
        write(p1p2[WRITE], &numero, sizeof(numero));
        close(p1p2[WRITE]);
        exit(0);
    }
    else if (pid > 0) // esegue il padre
    {
        close(p1p2[WRITE]);

        // p2 parte solo dentro questo if
        int p2p0[2];
        pipe(p2p0);
        int pid2 = fork();
        if (pid2 == 0) // esegue p2, il secondo figlio
        {
            read(p1p2[READ], &numero, sizeof(int));
            close(p1p2[READ]);

            numero = numero * numero;
            printf("%d\n", numero);

            // fflush(stdout);
            // write(1, &numero, sizeof(int));

            close(p2p0[READ]);
            write(p2p0[WRITE], &numero, sizeof(int));
            close(p2p0[WRITE]);

            exit(0);
        }
        if (pid2 > 0) // esegue il padre
        {
            wait(&pid);
            close(p1p2[READ]);

            close(p2p0[WRITE]);
            read(p2p0[READ], &numero, sizeof(int));
            close(p2p0[READ]);

            char stringa[10];
            sprintf(stringa, "%d", numero);

            int fd = open(argv[1], O_WRONLY, 777);
            write(fd, stringa, strlen(stringa));
            close(fd);
            exit(0);
        }
    }
}