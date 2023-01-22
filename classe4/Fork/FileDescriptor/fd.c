#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int status;      // Variabile per memorizzare lo stato di terminazione del figlio
    int p1 = fork(); // Crea un nuovo processo figlio
    if (p1 == 0)
    {
        // Codice eseguito dal figlio
        int myPID = getpid(); // Recupera il PID del figlio
        printf("Sono il figlio e questo è il mio PID: %d\n", myPID);
        char str[30]; // Stringa per costruire il comando da eseguire con system()

        /*sprintf(str, "ls -l /proc/%d/fd | wc -l", myPID);*/
        sprintf(str, "ls -l /proc/%d/fd", myPID); // Costruisce il comando "ls -l /proc/[PID del figlio]/fd"
        system(str);                              // Esegue il comando
        exit(0);                                  // Termina il processo figlio
    }
    else if (p1 > 0)
    {
        // Codice eseguito dal padre
        printf("Sono il padre e questo è il mio PID: %d\n", getpid());
        wait(&status); // Aspetta che il figlio termini
        printf("Il figlio ha terminato\n");
    }
    return 0;
}