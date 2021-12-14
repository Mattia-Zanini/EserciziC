#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        int numero;
        int numeri[ARRAY_SIZE] = {19, 34, 67, 98, 2, 23, 91, 7, 10, 85};
        close(canale1[READ]);  //scive solo sul canale1
        close(canale2[WRITE]); //legge solo sul canale2
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            write(canale1[WRITE], &numeri[i], sizeof(int));
        }
        read(canale2[READ], &numero, sizeof(int));
        printf("Questo è il risultato del figlio: %d\n", numero);
    }
    else if (PID == 0)
    {
        int numero = 0;
        int tmp;
        close(canale1[WRITE]); //legge solo sul canale1
        close(canale2[READ]);  //scrive solo sul canale2
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            read(canale1[READ], &tmp, sizeof(int));
            numero = numero + tmp;
        }
        write(canale2[WRITE], &numero, sizeof(int));
        exit(1);
    }
}