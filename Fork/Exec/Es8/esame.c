#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define R 0
#define W 1

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    int p1p2[2];
    char data[100];
    pipe(p1p2);
    int pid = fork();
    if (pid == 0)
    { // figlio 1
        close(p1p2[R]);
        char tmp[50];
        while (1)
        {
            printf("Inserisci una stringa:\n");
            scanf("%s", tmp);
            if (strcasecmp("esci", tmp) == 0)
            {
                break;
            }
            strcat(tmp, "\n");
            strcat(data, tmp);
            // printf("%s", data);
        }
        // printf("%ld", sizeof(data));
        // write(p1p2[W], data, sizeof(data));
        close(W);
        dup(p1p2[W]);
        close(p1p2[W]);
        printf("%s", data);
        exit(0);
    }
    pid = fork();
    if (pid == 0)
    { // figlio 2
        close(p1p2[W]);
        close(R);
        dup(p1p2[R]);
        close(p1p2[R]);
        int file = open(argv[1], O_WRONLY);
        close(W);
        dup(file);
        execl("/usr/bin/sort", "sort", NULL);
        exit(0);
    }
    // padre
    close(p1p2[R]);
    close(p1p2[W]);
    wait(&pid);
    return 0;
}