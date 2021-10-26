#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *in_file;
    char a, toFind = 'a';
    int nChar = 0;

    in_file = fopen("ciao.txt", "r");
    while (1){
        a = fgetc(in_file);
        if(a == toFind){
            nChar++;
        }
        else if(a == EOF){
            break;
        }

    }
    printf("Sono stati trovati: %d caratteri uguali a quella da cercare\n", nChar);
    return 0;
}