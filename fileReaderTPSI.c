#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fsize(FILE *in_file);

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
            int fileSize = fsize(in_file) - 1;//meno l'EOF
            printf("Il File ha una lunghezza pari a: %d\n", fileSize);
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