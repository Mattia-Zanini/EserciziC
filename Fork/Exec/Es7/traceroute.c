#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define R 0
#define W 1

// traceroute google.com | awk '{print $4}' | tail -n +2

int main()
{
    int p1, p2, p3, p1p2[2], p2p3[2], p3p0[2];
    char *ptr, buffer[1], valore[100];
    double tot = 0;

    pipe(p1p2);
    p1 = fork();
    if (p1 == 0) // traceroute
    {
        close(W); // stdout
        dup(p1p2[W]);
        close(p1p2[W]);
        close(p1p2[R]);

        execl("/usr/sbin/traceroute", "traceroute", "google.com",
              NULL);
        return -1;
    }
    else
    {
        pipe(p2p3);
        p2 = fork();
        if (p2 == 0) // awk
        {
            close(R); // stdin
            dup(p1p2[R]);
            close(p1p2[W]);
            close(p1p2[R]);

            close(W); // stdout
            dup(p2p3[W]);
            close(p2p3[W]);
            close(p2p3[R]);

            execl("/bin/awk", "awk", "{print $4}", NULL);
            return -1;
        }
        else
        {
            pipe(p3p0);
            p3 = fork(); // tail -n +2
            if (p3 == 0)
            {
                close(R); // stdin
                dup(p2p3[R]);
                close(p2p3[W]);
                close(p2p3[R]);

                close(W); // stdout
                dup(p3p0[W]);
                close(p3p0[W]);
                close(p3p0[R]);

                execl("/bin/tail", "tail", "-n", "+2", NULL);
                return -1;
            }
            else // padre
            {
                close(p1p2[W]);
                close(p1p2[R]);
                close(p2p3[W]);
                close(p2p3[R]);
                close(p3p0[W]);

                wait(&p3);

                int nope = 0;
                int nread = 0;

                while ((nread = read(p3p0[0], buffer, 1)) > 0)
                {
                    /*if ((buffer[0] != '\n' || buffer[0] != '(' || buffer[0] != ')') && nope == 0)
                    {
                        strncat(valore, &buffer[0], sizeof(buffer[0]));
                        printf("ok");
                    }*/
                    if (buffer[0] == '\n')
                    {
                        printf("Ho letto la riga: %s", valore);
                        tot = tot + strtod(valore, &ptr);
                        valore[0] = '\0';
                    }
                    strncat(valore, &buffer[0], sizeof(buffer[0]));
                    printf("Ho letto questo: %c", buffer[0]);
                    /*
                    else if (buffer[0] == '(')
                    {
                        nope = 1;
                    }
                    else if (buffer[0] == ')')
                    {
                        nope = 0;
                    }*/
                }
                printf("%.2lf\n", tot);
            }
        }
    }
}
