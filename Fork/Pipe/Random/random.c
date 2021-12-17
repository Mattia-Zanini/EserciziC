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
            numeri[i] = rand() % 200; //per limitare il range dei numeri casuali da 0 a 199
            printf("Questo è il numero generato: %d\n", numeri[i]);
        }
        close(canale1[READ]);  //scive solo sul canale1
        close(canale2[WRITE]); //legge solo sul canale2
        write(canale1[WRITE], numeri, sizeof(int) * ARRAY_SIZE);
        read(canale2[READ], &numero, sizeof(int));
        printf("Questo è il risultato del figlio: %d\n", numero);
    }
    else if (PID == 0)
    {
        int numero = 0;
        int tmp[ARRAY_SIZE];
        close(canale1[WRITE]); //legge solo sul canale1
        close(canale2[READ]);  //scrive solo sul canale2
        read(canale1[READ], tmp, ARRAY_SIZE * sizeof(int));
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            numero = numero + tmp[i];
        }
        write(canale2[WRITE], &numero, sizeof(int));
        exit(1);
    }
}