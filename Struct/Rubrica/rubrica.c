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

int ContaRighe(FILE *rubrica_input, char filename[])
{
    if ((rubrica_input = fopen(filename, "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(1);
    }
    int righe = 0;
    while (!feof(rubrica_input))
    {
        char c = fgetc(rubrica_input);
        if (c == '\n')
            righe++;
    }
    righe++;
    fclose(rubrica_input);
    printf("Il file possiede %d righe\n", righe);
    return righe;
}

void MostraRubrica(char filename[], FILE *rubrica_input, int righe)
{
    if ((rubrica_input = fopen(filename, "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(1);
    }
    PERSONA_T persone[righe];
    int pos = 0;
    while (!feof(rubrica_input))
    {
        fscanf(rubrica_input, "%s %s %s", persone[pos].nome, persone[pos].cognome, persone[pos].numeroTelefonico);
        pos++;
    }
    fclose(rubrica_input);
    for (int i = 0; i < righe; i++)
    {
        printf("%s %s %s\n", persone[i].nome, persone[i].cognome, persone[i].numeroTelefonico);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 4)
    {
        printf("Argomenti errati\n");
    }
    else
    {
        FILE *rubrica_input;
        int righe = ContaRighe(rubrica_input, argv[1]);
        MostraRubrica(argv[1], rubrica_input, righe);
    }
    return 0;
}

//https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file