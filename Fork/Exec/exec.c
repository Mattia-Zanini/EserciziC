#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    char fileName[] = "file.txt";
    int fd[2];
    pipe(fd);
    int p1 = fork();
    if (p1 == 0) //figlio 1
    {
        close(1);
        dup(fd[1]);
        close(fd[1]);
        execl("/bin/bash", "cat", "file.txt", NULL);
        exit(0);
    }
    else if (p1 > 0)
    {
        int p2 = fork();
        if (p2 == 0) //figlio 2
        {
            close(0);
            dup(fd[0]);
            close(fd[0]);
            char cmd[] = "wc -l";
            execl("/bin/bash", cmd, NULL);
            exit(0);
        }
        else if (p2 > 0)
        {
            wait(&status);
            printf("Il figli hanno terminato\n");
        }
    }
    return 0;
}