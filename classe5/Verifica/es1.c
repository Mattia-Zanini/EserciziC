#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 30

int NumeroLettera(char *w, char c)
{
    int n = 0;
    for (int i = 0; i < strlen(w); i++)
    {
        if (w[i] == c)
            n++;
    }
    return n;
}

int main()
{
    char word[WORD_LENGTH];
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int nAlphabet[strlen(alphabet)];

    // printf("numero lettere alfabeto: %ld\n", strlen(alphabet));

    printf("Scrivi una parola\n");
    scanf("%s", word);
    printf("Ecco la tua parola: %s\n", word);

    for (int i = 0; i < strlen(alphabet); i++)
    {
        nAlphabet[i] = NumeroLettera(word, alphabet[i]);
    }

    for (int i = 0; i < strlen(alphabet); i++)
    {
        if (nAlphabet[i] > 0)
            printf("Lettera %c: %d ripetizioni\n", alphabet[i], nAlphabet[i]);
    }
}