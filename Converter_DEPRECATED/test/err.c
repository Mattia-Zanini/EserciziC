/* In general it's good to include also the header of the current .c,
   to avoid repeating the prototypes */
#include "err.h"
#include <stdio.h>
#include <string.h>

void ErrorWrite(int txtColor1, char txt1[], int txtColor2, char txt2[])
{
    ChangeTextColor(txtColor1);
    printf("%s", txt1);
    ChangeTextColor(txtColor2);
    printf("%s", txt2);
}

// check the file extension, which must be .dg
int GoodExtension(char filename[])
{
    int length = strlen(filename);
    if (filename[length - 2] == 'd' && filename[length - 1] == 'g')
    {
        return 0; // good extension
    }
    return -1; // bad extension
}

void ChangeTextColor(int id)
{
    switch (id)
    {
    case -1:
        printf("\033[0m"); // DEFAULT COLOR
        break;
    case 0:
        printf("\033[0;30m"); // BLACK
        break;
    case 1:
        printf("\033[1;31m"); // RED
        break;
    case 2:
        printf("\033[0;32m"); // GREEN
        break;
    case 3:
        printf("\033[0;33m"); // YELLOW
        break;
    case 4:
        printf("\033[0;34m"); // BLUE
        break;
    case 5:
        printf("\033[0;35m"); // PURPLE
        break;
    case 6:
        printf("\033[0;36m"); // CYAN
        break;
    case 7:
        printf("\033[0;37m"); // WHITE
        break;
    }
}