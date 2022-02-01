#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    int fd[2];
    pipe(fd);
    int p1 = fork();
    if (p1 == 0) //figlio 1
    {
        close(1);
        dup(fd[1]);
        close(fd[1]);
        close(fd[0]);
        execl("/bin/cat", "cat", "file.txt", NULL);
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
            close(fd[1]);
            char cmd[] = "wc -l";
            execl("/bin/wc", cmd, NULL);
            exit(0);
        }
        else if (p2 > 0)
        {
            wait(&status);
            close(fd[0]);
            close(fd[1]);
            printf("Il figli hanno terminato\n");
        }
    }
    return 0;
}