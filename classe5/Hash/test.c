#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_STRINGS 1000000
#define MIN_CHARS 3
#define MAX_CHARS 20

#define ASCII_START 32
#define ASCII_END 126

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

char *generateRandomString(int size)
{
    int i;
    char *res = malloc(size + 1);

    for (i = 0; i < size; i++)
    {
        int key = (rand() % (ASCII_END - ASCII_START)) + ASCII_START;
        res[i] = (char)key;
        if (key == 92 || key == 32 || key == 34)
            i--;
    }
    res[i] = '\0';
    return res;
}

int main()
{
    srand(time(NULL));
    int percentage = 0;
    char *strings[18][N_STRINGS];
    char *str;
    printf("Starting to generate random strings\n");
    for (int i = 0; i < N_STRINGS; i++)
    {
        int n = randnum(MIN_CHARS, MAX_CHARS);
        str = generateRandomString(n);
        // printf("L parola: %ld\n", strlen(str));
        strings[strlen(str) - 3][i] = str;
    }
    printf("Ultima parola: %s\n", str);
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < N_STRINGS; j++)
        {
            printf("Parola assegnata: %s\n", strings[i][j]);
        }
    }

    printf("End\n");
    return 0;
}