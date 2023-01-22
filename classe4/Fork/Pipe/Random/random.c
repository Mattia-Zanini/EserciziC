/*
Questo programma utilizza la funzione fork() per creare un processo figlio e due pipe,
canale1 e canale2, per comunicare tra il processo padre e figlio.

La funzione pipe() crea una pipe e restituisce due file descriptor, uno per la lettura e uno
per la scrittura. In questo caso, creiamo due pipe chiamate canale1 e canale2.

La funzione fork() crea un nuovo processo figlio. Se la chiamata è riuscita, fork() restituirà 0
al processo figlio e il pid del figlio al processo padre. In caso di errore, restituirà -1.

Il codice all'interno del primo if (PID < 0) gestisce gli errori generati dalla fork().

Il codice all'interno del secondo if (PID > 0) viene eseguito solo dal padre. Il padre genera
casualmente 10 numeri compresi tra 0 e 11 e li stampa a schermo. Poi utilizza la pipe canale1 per
scrivere l'array di numeri generati al figlio. Successivamente, utilizza la pipe canale2 per leggere
 il risultato del figlio (la somma dei numeri generati) e lo stampa a schermo.

Il codice all'interno del terzo if (PID == 0) viene eseguito solo dal figlio. Il figlio utilizza
la pipe canale1 per leggere l'array di numeri generati dal padre, calcola la somma di questi numeri
e la utilizza la pipe canale2 per inviare il risultato al padre.

Infine, il codice chiude i file descriptor non utilizzati dai due processi per evitare problemi di sincronizzazione.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define READ 0
#define WRITE 1
#define ARRAY_SIZE 10

int main()
{
    int canale1[2], canale2[2];
    pipe(canale1);
    pipe(canale2);
    int PID = fork();
    if (PID < 0)
    {
        printf("errore durante la generazione del processo figlio\n");
        exit(1);
    }
    else if (PID > 0)
    {
        srand(time(NULL));
        int numero;
        int numeri[ARRAY_SIZE]; // = {19, 34, 67, 98, 2, 23, 91, 7, 10, 85};
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            numeri[i] = rand() % 12; // per limitare il range dei numeri casuali da 0 a 199
            printf("Questo è il numero generato: %d\n", numeri[i]);
        }
        close(canale1[READ]);  // scive solo sul canale1
        close(canale2[WRITE]); // legge solo sul canale2
        write(canale1[WRITE], numeri, sizeof(int) * ARRAY_SIZE);
        read(canale2[READ], &numero, sizeof(int));
        printf("Questo è il risultato del figlio: %d\n", numero);
    }
    else if (PID == 0)
    {
        int numero = 0;
        int tmp[ARRAY_SIZE];
        close(canale1[WRITE]); // legge solo sul canale1
        close(canale2[READ]);  // scrive solo sul canale2
        read(canale1[READ], tmp, ARRAY_SIZE * sizeof(int));
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            numero = numero + tmp[i];
        }
        write(canale2[WRITE], &numero, sizeof(int));
        exit(1);
    }
}