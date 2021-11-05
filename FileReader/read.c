#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *in_File;
    int find = 0;
    //legge i file che sono nella stessa cartella
    char fileInput[strlen(argv[1])];
    strcpy(fileInput, argv[1]);
    printf("Questo e' il file input da cercare: %s\n", fileInput);

    char fileOutput[strlen(argv[2])];
    strcpy(fileOutput, argv[2]);
    printf("Questo e' il file ouput da cercare: %s\n", fileOutput);

    if (strcmp(argv[3], "-c") == 0)
    {
        in_File = fopen(fileInput, "r");
        char tmpChar, toFind = argv[4][0];
        if (in_File != NULL)
        { //quando trova il file
            printf("File di input trovato e aperto\n");
            while (1)
            {
                tmpChar = fgetc(in_File);
                if (tmpChar == toFind)
                {
                    find++;
                }
                else if (tmpChar == EOF)
                {
                    break;
                }
            }
        }
        else //quando non trova il file
        {
            printf("File di input non trovato\n");
        }
        printf("File di input chiuso\n");
        fclose(in_File);
        //file di uscita
        FILE *out_File = fopen(fileOutput, "w+"); // write + overwrite
        if (out_File != NULL)
        { //quando trova il file
            printf("File di output trovato e aperto\n");
        }
        else //quando non trova il file
        {
            printf("File di output non trovato\n");
        }
        fprintf(out_File, "Nel file sono stati trovati %d caratteri che corrispondono a '%c'\n", find, toFind);
        fclose(out_File);
        printf("File di output chiuso\n");
        printf("Sono stati trovati: %d caratteri uguali a quello da cercare\n", find);
    }
    else if (strcmp(argv[3], "-p") == 0)
    {
        in_File = fopen(fileInput, "r");
        long stringLength = strlen(argv[4]);
        int streak = 0;
        char tmpChar, toFind[stringLength];
        printf("La parola da cercare e' lunga: %ld caratteri\n", stringLength);
        strcpy(fileInput, argv[4]);
        if (in_File != NULL)
        { //quando trova il file
            printf("File di input trovato e aperto\n");
            while (1)
            {
                tmpChar = fgetc(in_File);
                if (tmpChar == fileInput[streak])
                {
                    streak++;
                }
                else if (tmpChar == EOF)
                {
                    break;
                }
                else
                {
                    streak = 0;
                }
                if (streak == stringLength - 1) //perchè in stringLenght è stato conteggiato anche '\0'
                {
                    find++;
                    streak = 0;
                }
            }
            printf("Stringa da cercare: %s\n", argv[4]);
        }
        else //quando non trova il file
        {
            printf("File di input non trovato\n");
        }
        printf("File di input chiuso\n");
        fclose(in_File);
        //file di uscita
        FILE *out_File = fopen(fileOutput, "w+"); // write + overwrite
        if (out_File != NULL)
        { //quando trova il file
            printf("File di output trovato e aperto\n");
        }
        else //quando non trova il file
        {
            printf("File di output non trovato\n");
        }
        fprintf(out_File, "Nel file sono state trovate %d parole che corrispondono a '%s'\n", find, argv[4]);
        fclose(out_File);
        printf("File di output chiuso\n");
        printf("Sono stati trovate: %d parole uguali a quella da cercare\n", find);
    }
    return 0;
}