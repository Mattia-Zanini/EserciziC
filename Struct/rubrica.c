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

void mostraRubrica(char *argv[])
{
    FILE *rubrica_input;
    if ((rubrica_input = fopen(argv[1], "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(1);
    }
    PERSONA_T persone[10];
    int nNumeri = 0;
    while (!feof(rubrica_input))
    {
        if ((nNumeri % 3) == 0)
            nNumeri = nNumeri / 3;
        fscanf(rubrica_input, "%s %s %s", persone[nNumeri].nome, persone[nNumeri].cognome, persone[nNumeri].numeroTelefonico);
        nNumeri++;
    }
    fclose(rubrica_input);
    for (int i = 0; i < nNumeri; i++)
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
    }
    return 0;
}