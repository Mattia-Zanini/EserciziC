#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (strcmp(argv[3], "-c") == 0)
    {
        //cerca un carattere
        printf("Cerco un carattere\n");
        FILE *fp;
        if((fp = fopen(argv[1], "r")) == NULL){
            printf("File %s non trovato o impossibile da aprire\n", argv[1]);
            int lenghtArray = 0;
            lenghtArray = strlen(argv[0]);
            printf("%s questo e' il percorso", argv[0]);
            int toRemove = lenghtArray - 18;
            exit(1);
        }
        else{
            printf("File trovato e aperto");
            fclose(fp);
        }
    }
    else if (strcmp(argv[3], "-p") == 0)
    {
        //cerca una parola
        printf("Cerco una parola\n");
    }
}