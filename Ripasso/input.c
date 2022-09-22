#include <stdio.h>

int Ritorna5()
{
    printf("Muahahhaahha\n");
    return 5;
}

void Ciao()
{
    printf("Ciao stronzo\n");
    printf("Prova 1: %c\n", 'f');
    printf("Prova 2: %s\n", "wow onwaijnwdijnadijnaijdnian okandn ciao");
    printf("Prova 3: %f\n", 5.23648889811);
    printf("Prova 4: %ld\n", 9119952391561989489);
    printf("Questo è il valroe che mi è stato ritornato: %d\n", Ritorna5());
}

int main()
{
    Ciao();
    return 0;
}