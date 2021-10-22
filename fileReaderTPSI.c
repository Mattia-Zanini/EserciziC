#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GetPath(char *argv[], int pathLenght, char path[]);

int main(int argc, char *argv[])
{
    if (strcmp(argv[3], "-c") == 0)
    {
        //cerca un carattere
        printf("Cerco un carattere\n");
        FILE *fp;
        //ritaglio percorso file
        int pathLenght = strlen(argv[0]);
        char path[pathLenght - 19];
        GetPath(argv, pathLenght, path);
        //inizializzo l'array che conterrà il percorso completo
        char fileIN[] = "";
        //aggiungo il percorso ritagliato e il nome del file
        strcat(fileIN, path);
        strcat(fileIN, argv[1]);
        printf("Questo e' il percorso completo: %s\n", fileIN);
        //controllo se c'è il file
        if ((fp = fopen(argv[1], "r")) == NULL)
        {
            printf("File %s non trovato o impossibile da aprire\n", argv[1]);
            exit(1);
        }
        else
        {
            printf("File trovato e aperto");
            fclose(fp);
        }
        return 0;
    }
    else if (strcmp(argv[3], "-p") == 0)
    {
        //cerca una parola
        printf("Cerco una parola\n");
    }
}
void GetPath(char *argv[], int pathLenght, char path[])
{
    char fullPath[pathLenght];
    strcpy(fullPath, argv[0]);
    for (int i = 0; i < pathLenght - 19; i++)
    {
        path[i] = fullPath[i];
        printf("%c\n", path[i]);
        if(i = (pathLenght - 19)){
            printf("prova\n");
        }
    }
    printf("Questo e' il percorso ritagliato: %s\n", path);
    printf("Questo e' il percorso assoluto: %s\n", argv[0]);
}