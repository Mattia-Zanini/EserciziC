#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define ARGC_VALID 6

void replaceChars(char string[MAX_SIZE][MAX_SIZE], int lenght, char *str, char chrDelete, char chrReplace, int *replaced)
{
    printf("carattere da rimpiazzare: %c\n", chrDelete);
    printf("carattere che rimpiazzare: %c\n", chrReplace);
    for (int i = 0; i < lenght; i++)
    {
        for (int j = 0; j < strlen(string[i]); j++)
        {
            if (string[i][j] == chrDelete)
            {
                string[i][j] = chrReplace;
                ++(*replaced);
                // printf("rimpiazzata una lettera\n");
            }
        }
        int strLength = strlen(string[i]);
        char tmp[strLength];
        sprintf(tmp, "%s ", string[i]);
        strcat(str, tmp);
    }
}

void wirteOutput(char *outputFile, char *str)
{
    FILE *output;
    if ((output = fopen(outputFile, "w")) == NULL)
    {
        printf("errore nell'apertura del file output");
        exit(2);
    }
    fprintf(output, "%s", str);
    fclose(output);
}

int main(int argc, char *argv[])
{
    if (argc != ARGC_VALID || argv[3][1] != 's')
    {
        printf("Argomenti errati\n");
    }
    else if (argv[4][0] == argv[5][0])
    {
        printf("Non ha senso cambiare un carattere con un medesimo uguale\n");
    }
    else
    {
        FILE *input;
        char string[MAX_SIZE][MAX_SIZE];
        char str[MAX_SIZE];
        int nWords = 0, nReplaced = 0;
        if ((input = fopen(argv[1], "r")) == NULL)
        {
            printf("errore nell'apertura del file\n");
            exit(1);
        }
        while (!feof(input))
        {
            fscanf(input, "%s\t", string[nWords]);
            nWords++;
        }
        fclose(input);
        replaceChars(string, nWords, str, argv[4][0], argv[5][0], &nReplaced);
        wirteOutput(argv[2], str);
    }
    return 0;
}