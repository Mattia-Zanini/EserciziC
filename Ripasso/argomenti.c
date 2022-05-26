#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    printf("Questo è il numero di argomenti del tuo programma: %d\n", argc);
    for(int i = 0; i < argc; i++){
        printf("Questo è l'argomento numero %d: %s\n", i+1, argv[i]);
    }
    return 0;
}