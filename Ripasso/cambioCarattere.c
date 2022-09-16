#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *cambioChar(char frase[])
{
    printf("Parola prima di cambiare le lettere: %s\n", frase);
    for (int i = 0; i < strlen(frase); i++)
    {
        if (frase[i] == 'c')
            frase[i] = 'n';
    }
    return frase;
}

int main(int argc, char *argv[])
{
    char *prova = cambioChar(argv[1]);
    printf("Parola cambiata: %s\n", prova);
    printf("Lunghezza della parola: %ld\n", strlen(prova));
    return 0;
}