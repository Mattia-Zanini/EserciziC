#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("inserisci un numero\n");
    int a;
    scanf("%d", &a);
    int son = fork();
    if (son == 0)
    {
        printf("Figlio: Questo è il mio PID: %d\n", getpid());
        a = a + 15;
        printf("Figlio: Questo è il risultato: %d\n", a);
        exit(0);
    }
    else if (son > 0)
    {
        printf("Padre: Questo è il mio PID: %d\n", getpid());
        waitpid(son, 0, 0);
        a = a + 10;
        printf("Padre: Questo è il risultato: %d\n", a);
        printf("Padre: Il figlio ha terminato\n");
    }
    return 0;
}