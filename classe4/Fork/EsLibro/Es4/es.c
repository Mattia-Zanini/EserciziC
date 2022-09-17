///  \file   es.c
///  \brief
///  \date   Il file è stato creato l'19/11/2021
///  \author Mattia Zanini

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CHAR 10

void toUpLowCase(char string[])
{
    int dim = strlen(string);
    string[0] = toupper(string[0]);
    for (int i = 1; i < dim; i++)
        string[i] = tolower(string[i]);
}

/**
 *  \fn     int main()
 *  \brief
 *  \return int: indica come è terminato il programma
 */

int main()
{
    FILE *fp;
    if ((fp = fopen("output.txt", "w+")) == NULL)
    {
        printf("impossibile accedere al file\n");
        exit(2);
    }
    char nome[MAX_CHAR];
    char cognome[MAX_CHAR];
    printf("Scrivi un nome\n");
    scanf("%s", nome);
    printf("Scrivi un cognome\n");
    scanf("%s", cognome);
    int PID = fork();
    if (PID < 0)
    {
        printf("Errore nella generazione del processo figlio\n");
        exit(3);
    }
    else if (PID == 0) //processo figlio
    {
        sleep(5);
        printf("Figlio: Leggo quello che il padre ha scritto\n");
        if ((fp = fopen("output.txt", "r")) == NULL)
        {
            printf("Figlio: Impossibile accedere al file\n");
            exit(2);
        }
        fscanf(fp, "%s %s", nome, cognome);
        printf("Figlio: %s %s\n", nome, cognome);
        printf("Figlio: Ho terminato\n");
        exit(1);
    }
    else //processo padre
    {
        toUpLowCase(nome);
        toUpLowCase(cognome);
        fprintf(fp, "%s %s\n", nome, cognome);
        fclose(fp);
        if (remove("output.txt") == 0)
            printf("Padre: Il file è stato eliminato con successo\n");
        else
            printf("Padre: Il file non è stato eliminato\n");
        wait(&PID);
        printf("Padre: Il processo figlio ha terminato\n");
    }
    return 0;
}