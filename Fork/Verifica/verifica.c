#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct
{
    char nome[10];
    char cognome[10];
    char ruolo[14];
} GIOCATORE_T;

int ContaRighe(FILE *input, char filename[])
{
    if ((input = fopen(filename, "r")) == NULL)
    {
        printf("impossibile leggere il file\n");
        exit(1);
    }
    int righe = 0;
    char tmp;
    while (!feof(input))
    {
        tmp = fgetc(input);
        if (tmp == '\n')
            righe++;
    }
    if (tmp == EOF && righe != 0)
        righe++;
    fclose(input);
    return righe;
}

void LetturaFile(FILE *input, char filename[], int righe, GIOCATORE_T calciatori[])
{
    if ((input = fopen(filename, "r")) == NULL)
    {
        printf("impossibile leggere il file\n");
        exit(1);
    }
    GIOCATORE_T squadra[righe];
    for (int i = 0; !feof(input); i++)
    {
        fscanf(input, "%s %s %s", squadra[i].nome, squadra[i].cognome, squadra[i].ruolo);
        strcpy(calciatori[i].nome, squadra[i].nome);
        strcpy(calciatori[i].cognome, squadra[i].cognome);
        strcpy(calciatori[i].ruolo, squadra[i].ruolo);
    }
    fclose(input);
}

void MostraAttacanti(GIOCATORE_T output[], int length)
{
    for (int i = 0; i < length; i++)
        printf("%s %s\n", output[i].nome, output[i].nome);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("argomenti errati\n");
        exit(1);
    }
    FILE *fp;
    int righe = ContaRighe(fp, argv[1]);
    GIOCATORE_T giocatori[righe];
    LetturaFile(fp, argv[1], righe, giocatori);
    int attaccanti = 0;
    for (int i = 0; i < righe; i++)
    {
        if (strcmp(giocatori[i].ruolo, "attaccante") == 0)
            attaccanti++;
    }
    GIOCATORE_T _attaccanti[attaccanti];
    int tmp = 0;
    for (int i = 0; i < righe; i++)
    {
        if (strcmp(giocatori[i].ruolo, "attaccante") == 0)
        {
            strcpy(_attaccanti[tmp].nome, giocatori[i].nome);
            strcpy(_attaccanti[tmp].cognome, giocatori[i].cognome);
            tmp++;
        }
    }
    int PID = fork();
    if (PID < 0)
    {
        printf("errore con la generazione del processo figlio\n");
        exit(1);
    }
    else if (PID == 0)
    {
        printf("Figlio: Eseguo\n");
        MostraAttacanti(_attaccanti, attaccanti);
        exit(1);
    }
    else if (PID > 0)
    {
        int status;
        wait(&status);
        printf("Padre: Il processo figlio ha terminato con stato: %d\n", status);
    }
    return 0;
}