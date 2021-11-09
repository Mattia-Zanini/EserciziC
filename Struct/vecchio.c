//  \file   vecchio.c
//  \brief  mostra a schermo il più vecchio tra le 4 persone prese in input dall'utente
//  \date   Il file è stato creato l'8/11/2021

#include <stdio.h>

#define DIM 4
#define MAX_CHAR 10

typedef struct
{
    char nome[MAX_CHAR];
    char cognome[MAX_CHAR];
    int eta;
} PERSONA_T;
/**
 *  \fn     void vecchio(PERSONA_T *persone)
 *  \brief  funzione che ricevendo come parametro il puntatore dell'array "persone" trova la persona più vecchia tra quelle inserite nell'array
 *  \param  PERSONA_T *persone: puntatore dell'array persone, contenuto nel main
 *  \date   8/11/2021
 *  \author Mattia Zanini
 *  \file   vecchio.c
 */

void vecchio(PERSONA_T *persone)
{
    int posVecchio = 0;
    for (int i = 1; i < DIM; i++)
    {
        if (persone[i].eta < persone[i - 1].eta)
        {
            posVecchio = i - 1;
        }
        else
        {
            posVecchio = i;
        }
    }
    printf("Il più vecchio è: %s\n", persone[posVecchio].nome);
}

/**
 *  \fn     PERSONA_T inserisci(int nPersona)
 *  \brief  funzione che avvisa l'utente dei dati da inserire, rispettivamente della persona pari al valore int passato per parametro, e prende in input i dati che l'utente fornisce
 *  \param  int nPersona: valore int del ciclo for con la quale viene chaiamta questa funzione, ovvero il numero della persona da inserire
 *  \return PERSONA_T: la funzione ritorna una variabile complessa
 *  \date   8/11/2021
 *  \author Mattia Zanini
 *  \file   vecchio.c
 */

PERSONA_T inserisci(int nPersona)
{
    PERSONA_T p;
    printf("Inserisci un nome per la persona n°%d\nIl nome deve avere un massimo di 10 caratteri\n", nPersona);
    scanf("%s", p.nome);
    printf("\nInserisci un cognome per la persona n°%d\nIl cognome deve avere un massimo di 10 caratteri\n", nPersona);
    scanf("%s", p.cognome);
    printf("\nInserisci un età per la persona n°%d\n", nPersona);
    scanf("%d", &p.eta);
    printf("\n");
    return p;
}

/**
 *  \fn     int main()
 *  \brief  funzione principale, dove viene creato l'array della variabile complessa "PERSONA_T" di dimensione pari a 4 "DIM", chiamando successivamente le altre funzioni necessarie per svolgere il compito del programma
 *  \return int: indica come è terminato il programma
 *  \date   8/11/2021
 *  \author Mattia Zanini
 *  \file   vecchio.c
 */

int main()
{
    PERSONA_T persone[DIM];
    for (int i = 0; i < DIM; i++)
    {
        persone[i] = inserisci(i + 1);
    }
    vecchio(persone);

    return 0;
}
