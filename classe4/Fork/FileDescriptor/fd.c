#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    int p1 = fork();
    if (p1 == 0)
    {
        int myPID = getpid();
        printf("Sono il figlio e questo è il mio PID: %d\n", myPID);
        char str[30];
        /*sprintf(str, "ls -l /proc/%d/fd | wc -l", myPID);*/
        sprintf(str, "ls -l /proc/%d/fd", myPID);
        system(str);
        exit(0);
    }
    else if (p1 > 0)
    {
        printf("Sono il padre e questo è il mio PID: %d\n", getpid());
        wait(&status);
        printf("Il figlio ha terminato\n");
    }
    return 0;
}