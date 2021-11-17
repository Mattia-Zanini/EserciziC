#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define ROW_LENGTH 40

int ContaRighe(FILE *fp, char filename[])
{
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Impossibile aprire il file\n");
        exit(4);
    }
    int righe = 0;
    char c;
    while (!feof(fp))
    {
        c = fgetc(fp);
        if (c == '\n')
            righe++;
    }
    if (c == EOF && righe != 0)
        righe++;
    fclose(fp);
    return righe;
}

int main()
{
    int pid1, pid2, pid3, status;
    pid1 = fork();
    if (pid1 == 0)
    {
        FILE *fp;
        if ((fp = fopen("output.txt", "w+")) == NULL)
        {
            printf("Figlio 1: Impossibile aprire il file\n");
        }
        else
        {
            int righe = ContaRighe(fp, "output.txt");
            char rows[ROW_LENGTH * righe];
            for (int i = 0; !feof(fp); i++)
            {
                rows[i] = fgetc(fp);
            }
            char row[] = "Figlio 1: Ciao sono il primo figlio\n";
            strcat(rows, row);
            fprintf(fp, "%s", rows);
        }
        fclose(fp);
        sleep(6);
        exit(1);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            FILE *fp;
            if ((fp = fopen("output.txt", "w+")) == NULL)
            {
                printf("Figlio 2: Impossibile aprire il file\n");
            }
            else
            {
                int righe = ContaRighe(fp, "output.txt");
                char rows[ROW_LENGTH * righe];
                for (int i = 0; !feof(fp); i++)
                {
                    rows[i] = fgetc(fp);
                }
                char row[] = "Figlio 2: Ciao sono il secondo figlio\n";
                strcat(rows, row);
                fprintf(fp, "%s", rows);
            }
            fclose(fp);
            sleep(4);
            exit(2);
        }
        else if (pid2 > 0)
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                FILE *fp;
                if ((fp = fopen("output.txt", "w+")) == NULL)
                {
                    printf("Figlio 3: Impossibile aprire il file\n");
                }
                else
                {
                    int righe = ContaRighe(fp, "output.txt");
                    char rows[ROW_LENGTH * righe];
                    for (int i = 0; !feof(fp); i++)
                    {
                        rows[i] = fgetc(fp);
                    }
                    char row[] = "Figlio 3: Ciao sono il terzo figlio\n";
                    strcat(rows, row);
                    fprintf(fp, "%s", rows);
                }
                fclose(fp);
                exit(3);
            }
            else if (pid2 > 0)
            {
                printf("Padre: Aspetto che il figlio più lento finisca di scrivere sul file\n");
                waitpid(pid1, &status, 0);
                printf("Padre: Ok i miei figli hanno appena finito, vado a leggere quello che hanno scritto\n");
                FILE *fp;
                if ((fp = fopen("output.txt", "r")) == NULL)
                {
                    printf("Padre: Impossibile aprire il file\n");
                }
                else
                {
                    char row[ROW_LENGTH];
                    while (fgets(row, sizeof(row), fp) != NULL)
                    {
                        puts(row);
                    }
                    printf("Questo è quello che i miei figli hanno scritto\n");
                }
                fclose(fp);
            }
        }
    }
    return 0;
}

/*
    char str[ROW_LENGTH * righe];
    for (int i = 0; !feof(fp); i++)
    {
        char tmp[ROW_LENGTH];
        if (i == 0)
            strcpy(str, tmp);
        else
            strcat(str, tmp);
    }
    */