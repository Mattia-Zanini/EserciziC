#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int err = open("error.txt", O_WRONLY);

    int status;
    int fd[2];
    pipe(fd);
    int p1 = fork();
    if (p1 == 0) // figlio 1
    {
        printf("PID di p1: %d\n", getpid());
        close(1);
        dup(fd[1]);
        close(fd[1]);
        close(fd[0]);
        // sleep(30);
        execl("/bin/cat", "cat", "file.txt", NULL);
        exit(0);
    }
    else if (p1 > 0)
    {
        int fd2[2];
        pipe(fd2);
        int p2 = fork();
        if (p2 == 0) // figlio 2
        {
            printf("PID di p2: %d\n", getpid());
            // pipe 1
            close(0); // stdin
            dup(fd[0]);
            close(fd[0]);
            close(fd[1]);

            // pipe 2
            close(1); // stdout
            dup(fd2[1]);
            close(fd2[1]);
            close(fd2[0]);

            // sleep(30);
            execl("/bin/wc", "wc", NULL);
            exit(0);
        }
        else if (p2 > 0)
        {
            int out = open("output.txt", O_WRONLY);

            // pipe 2
            close(0); // stdin
            dup(fd2[0]);
            close(fd2[0]);
            close(fd2[1]);

            printf("PID di p0: %d\n", getpid());

            close(1); // stdout
            dup(out);
            close(out);

            /*char str[30];
            sprintf(str, "ls -l /proc/%d/fd", getpid());
            system(str);*/

            wait(&status);
            close(fd[0]);
            close(fd[1]);

            // printf("Il figli hanno terminato\n");
        }
    }
    return 0;
}