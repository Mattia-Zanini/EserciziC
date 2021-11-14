#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 10

typedef struct
{
    char nome[MAX_CHAR];
    char cognome[MAX_CHAR];
    char numeroTelefonico[10];
} PERSONA_T;

int ContaRighe(FILE *rubrica, char filename[])
{
    if ((rubrica = fopen(filename, "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(1);
    }
    int righe = 0;
    char c;
    while (!feof(rubrica))
    {
        c = fgetc(rubrica);
        if (c == '\n')
            righe++;
    }
    if (c == '\n' && righe != 0)
        righe++;
    fclose(rubrica);
    printf("Il file possiede %d righe\n", righe);
    return righe;
}

void MostraRubrica(FILE *rubrica, char filename[], int righe)
{
    if ((rubrica = fopen(filename, "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(1);
    }
    PERSONA_T persone[righe];
    for (int i = 0; !feof(rubrica); i++)
        fscanf(rubrica, "%s %s %s", persone[i].nome, persone[i].cognome, persone[i].numeroTelefonico);
    fclose(rubrica);
    for (int i = 0; i < righe; i++)
        printf("%s %s %s\n", persone[i].nome, persone[i].cognome, persone[i].numeroTelefonico);
}

void AggiungiContatto(FILE *rubrica, char filename[], int righe, PERSONA_T nuovoContatto)
{
    if ((rubrica = fopen(filename, "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(1);
    }
    PERSONA_T persone[righe];
    for (int i = 0; !feof(rubrica); i++)
        fscanf(rubrica, "%s %s %s", persone[i].nome, persone[i].cognome, persone[i].numeroTelefonico);
    fclose(rubrica);
    persone[righe - 1] = nuovoContatto;
    int strLength = 32 * righe;
    char str[strLength];
    for (int i = 0; i < righe; i++)
    {
        char tmp[32];
        sprintf(tmp, "%s %s %s\n", persone[i].nome, persone[i].cognome, persone[i].numeroTelefonico);
        strcat(str, tmp);
    }
    if ((rubrica = fopen(filename, "w")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(2);
    }
    fprintf(rubrica, "%s", str);
    fclose(rubrica);
}

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 4)
    {
        printf("Argomenti errati\n");
    }
    else
    {
        FILE *rubrica;
        PERSONA_T nuovoContatto;
        int righe, risposta;
        system("clear"); //solo per LINUX
        do
        {
            printf("Digita il numero corrispondente a quello che vuoi fare:\n1) Mostra rubrica\n2) Salva contatto\n3) Elimina contatto\n4) Esci dal programma\n5) Pulisci la console\n\n");
            scanf("%d", &risposta);
            switch (risposta)
            {
            case 1:
                righe = ContaRighe(rubrica, argv[1]);
                MostraRubrica(rubrica, argv[1], righe);
                printf("\n\n");
                break;
            case 2:
                printf("Inserisci il nome del contatto che vuoi aggiungere\n");
                scanf("%s", nuovoContatto.nome);
                printf("Inserisci il cognome del contatto che vuoi aggiungere\n");
                scanf("%s", nuovoContatto.cognome);
                printf("Inserisci il numero telefonico del contatto che vuoi aggiungere\n");
                scanf("%s", nuovoContatto.numeroTelefonico);
                righe = ContaRighe(rubrica, argv[1]);
                righe++;
                AggiungiContatto(rubrica, argv[1], righe, nuovoContatto);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                system("clear");
                break;
            default:
                printf("comando non valido\n");
                break;
            }
        } while (risposta != 4);
    }
    return 0;
}

//https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file