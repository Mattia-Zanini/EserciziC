#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char toUpper(char toUP)
{
    switch (toUP)
    {
    case 'a':
        toUP = 'A';
        break;
    case 'b':
        toUP = 'B';
        break;
    case 'c':
        toUP = 'C';
        break;
    case 'd':
        toUP = 'D';
        break;
    case 'e':
        toUP = 'E';
        break;
    case 'f':
        toUP = 'F';
        break;
    case 'g':
        toUP = 'G';
        break;
    case 'h':
        toUP = 'H';
        break;
    case 'i':
        toUP = 'I';
        break;
    case 'j':
        toUP = 'J';
        break;
    case 'k':
        toUP = 'K';
        break;
    case 'l':
        toUP = 'L';
        break;
    case 'm':
        toUP = 'M';
        break;
    case 'n':
        toUP = 'N';
        break;
    case 'o':
        toUP = 'O';
        break;
    case 'p':
        toUP = 'P';
        break;
    case 'q':
        toUP = 'Q';
        break;
    case 'r':
        toUP = 'R';
        break;
    case 's':
        toUP = 'S';
        break;
    case 't':
        toUP = 'T';
        break;
    case 'u':
        toUP = 'U';
        break;
    case 'v':
        toUP = 'V';
        break;
    case 'w':
        toUP = 'W';
        break;
    case 'x':
        toUP = 'X';
        break;
    case 'y':
        toUP = 'Y';
        break;
    case 'z':
        toUP = 'Z';
        break;
    }
    return toUP;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Argomenti errati\n");
    }
    else
    {
        char toUP[1];
        toUP[0] = argv[1][0];
        int fd[2];
        int pipeStatus = pipe(fd); //crea una coppia di file descriptor, utilizzabili per una 'pipe'
        if (pipeStatus == 0)       //il pipe ha successo
        {
            int PID = fork();
            if (PID < 0)
            {
                printf("errore durante la creazione del processo figlio\n");
                exit(1);
            }
            else if (PID == 0) //processo figlio
            {
                toUP[0] = toUpper(toUP[0]);
                write(fd[1], toUP, 1); //accede al file descriptor di scrittura
                printf("Figlio: Ho terminato\n");
                exit(0);
            }
            else //processo padre
            {
                printf("Padre: Aspetto il processo figlio\n");
                wait(0);
                read(fd[0], toUP, 1); //accede al file descriptor di lettura
                printf("Padre: Questa è il tuo carattere in uppercase: %c\n", toUP[0]);
            }
        }
        else
        {
            printf("errore durante la creazione del collegamento");
        }
    }
    return 0;
}