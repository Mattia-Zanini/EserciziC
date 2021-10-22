#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fsize(FILE *in_file);
int searchCharacter(int fileSize, char *buff, char toFind);

int main(int argc, char *argv[])
{
    if (strcmp(argv[3], "-c") == 0)
    {
        //cerca un carattere
        printf("Cerco un carattere\n");
        char *path = realpath(argv[1], NULL); //ottiene il percorso del file
        FILE *in_file = fopen(path, "r");     // read only
        free(path);
        if (in_file == NULL)
        {
            printf("File %s non trovato o impossibile da aprire\n", argv[1]);
            exit(1);
        }
        else
        {
            printf("File trovato e aperto\n");
            int fileSize = fsize(in_file);
            printf("Il file ha un quantitativo di caratteri pari a: %d\n", fileSize - 1); //meno l'EOF
            char buff[fileSize];
            fgets(buff, fileSize, in_file);
            char toFind = argv[2][0];
            int nChars = searchCharacter(fileSize, buff, toFind);
            printf("Nel file sono presenti: %d caratteri uguali a %c\n", nChars, toFind); //meno l'EOF
            fclose(in_file);
            printf("File chiuso\n");
        }
        return 0;
    }
    else if (strcmp(argv[3], "-p") == 0)
    {
        //cerca una parola
        printf("Cerco una parola\n");
    }
}
int fsize(FILE *in_file)
{
    int prev = ftell(in_file);
    fseek(in_file, 0L, SEEK_END);
    int sz = ftell(in_file);
    fseek(in_file, prev, SEEK_SET); //go back to where we were
    return sz;
}
int searchCharacter(int fileSize, char *buff, char toFind)
{
    int nChar = 0;
    for (int i = 0; i < fileSize - 1; i++)
    {
        if(buff[i] == toFind)
            nChar++;
    }
    return nChar;
}