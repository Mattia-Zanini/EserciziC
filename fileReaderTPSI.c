#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 1000

int searchCharacter(char *buff, char toFind, FILE *in_file);

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
            char toFind = argv[4][0];
            char buff[256];
            int nChars = searchCharacter(buff, toFind, in_file);
            printf("Nel file sono presenti: %d caratteri uguali a %c\n", nChars, toFind); //meno l'EOF
            fclose(in_file);
            printf("File chiuso\n");
            //ottiene il percorso della cartella da dov eviene eseguito il codice
            char dirPath[PATH_MAX];
            if (getcwd(dirPath, sizeof(dirPath)) != NULL)
            {
                char file_OUT[FILENAME_MAX]; char pathSP[] = "/";
                strcat(dirPath, pathSP); strcpy(file_OUT, argv[2]); strcat(dirPath, file_OUT);
                FILE *out_file = fopen(dirPath, "w+"); // write + overwrite
                fprintf(out_file, "Nel file sono state trovati %d caratteri che corrispondono a '%c'\n", nChars, argv[4][0]);
                fclose(out_file);
                printf("Percorso dove il risultato e' stato salvato: %s\n", dirPath);
            }
            else
            {
                perror("getcwd() error");
                return 1;
            }
        }
    }
    else if (strcmp(argv[3], "-p") == 0)
    {
        //cerca una parola
        printf("Cerco una parola\n");
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
        }
    }
    return 0;
}
int searchCharacter(char *buff, char toFind, FILE *in_file)
{
    int nChar = 0;
    while (fgets(buff, 256, in_file) != NULL)
    {
        printf("Questa e' la riga: %s\n", buff);
        for (int i = 0; i < 256; i++)
        {
            if (buff[i] == toFind)
            {
                nChar++;
                printf("Questo dovrebbere essere uguale %c\n", buff[i]);
            }
        }
    }
    return nChar;
}