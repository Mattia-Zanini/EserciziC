#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define WORD_LENGTH 30
#define TRUE 1
#define FALSE 0

int GiaPresente(char w[], char c)
{
    for (int i = 0; i < strlen(w); i++)
}

int ParolaPiuLunga(char w[], char w2[])
{
    if (strlen(w) > strlen(w2))
    {
        printf("La parola più lunga è la prima: %s\n", w);
        return strlen(w);
    }
    else if (strlen(w) < strlen(w2))
    {
        printf("La parola più lunga è la seconda: %s\n", w2);
        return strlen(w2);
    }
    else
    {
        printf("La due parole sono lunghe uguali\n");
        return strlen(w);
    }
}

void LettereSuEntrambeParole(char w[], char w2[])
{
    int length = ParolaPiuLunga(w, w2);
    char ambedue[WORD_LENGTH];
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
            if (w[i] == w2[j])
                break;
        ambedue[i] = w[i];
    }
    printf("Lettere che entrambe le paorle contengono: %s\n", ambedue);
}

int Doppie(char w[])
{
    int nDoppie = 0;
    int length = strlen(w);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
            if (w[i] == w[j])
                nDoppie++;
        if (nDoppie > 1)
            return TRUE;
    }
    return FALSE;
}

void LetterePariDispari(char w[])
{
    int length = strlen(w);
    int nP = 0, nD = 0;
    char pari[length];
    char dispari[length];
    for (int i = 0; i < length; i++)
    {
        if (isalpha(w[i]))
        {
            if (i % 2 == 0)
            {
                pari[nP] = w[i];
                nP++;
            }
            else
            {
                dispari[nD] = w[i];
                nD++;
            }
        }
    }
    printf("Parola generata con lettere in posizione pari: %s\n", pari);
    printf("Parola generata con lettere in posizione dispari: %s\n", dispari);
}

int NumeroLettera(char w[], char lettera)
{
    int nChar = 0;
    for (int i = 0; i < strlen(w); i++)
        if (w[i] == lettera)
            nChar++;

    return nChar;
}

int NumeroConsonanti(char w[])
{
    int nConsonante = 0;
    int isConsonante = FALSE;
    char vocali[] = "aeiou";
    for (int i = 0; i < strlen(w); i++)
    {
        for (int j = 0; j < strlen(vocali); j++)
        {
            if (w[i] == vocali[j])
            {
                isConsonante = FALSE;
                break;
            }
            isConsonante = TRUE;
        }
        if (isConsonante == TRUE)
            nConsonante++;
    }

    return nConsonante;
}

int NumeroVocali(char w[])
{
    int nVocali = 0;
    char vocali[] = "aeiou";
    for (int i = 0; i < strlen(w); i++)
        for (int j = 0; j < strlen(vocali); j++)
            if (w[i] == vocali[j])
                nVocali++;

    return nVocali;
}

int SoloLettere(char w[])
{
    for (int i = 0; i < strlen(w); i++)
        if (isdigit(w[i]))
            return TRUE;

    return FALSE;
}

void PiuConsonanti(char w[], char w2[])
{
    int nConsonanti = NumeroConsonanti(w);
    int nConsonanti2 = NumeroConsonanti(w2);
    if (nConsonanti > nConsonanti2)
        printf("La parola che contiene più consonanti è la prima: %s\n", w);
    else if (nConsonanti < nConsonanti2)
        printf("La parola che contiene più consonanti è la seconda: %s\n", w2);
    else
        printf("La due parole hanno lo stesso numero di consonanti\n");
}

void PiuVocali(char w[], char w2[])
{
    int nVocali = NumeroVocali(w);
    int nVocali2 = NumeroVocali(w2);
    if (nVocali > nVocali2)
        printf("La parola che contiene più vocali è la prima: %s\n", w);
    else if (nVocali < nVocali2)
        printf("La parola che contiene più vocali è la seconda: %s\n", w2);
    else
        printf("La due parole hanno lo stesso numero di vocali\n");
}

int main()
{
    char word[WORD_LENGTH];
    char word2[WORD_LENGTH];
    char lett;
    printf("Inserisci una parola a piacere\n");
    scanf("%s", word);
    printf("Contiene numeri? (0 -> no, 1 -> si)\n%d\n", SoloLettere(word));
    printf("Contiene %d vocali\n", NumeroVocali(word));
    printf("Contiene %d consonanti\n", NumeroConsonanti(word));
    printf("Scegli una lettera e ti dirò quante volte compare nella parola\n");
    sleep(1);
    scanf("%c", &lett);
    printf("Contiene %d lettere\n", NumeroLettera(word, lett));
    LetterePariDispari(word);

    printf("Inserisci una parola a piacere\n");
    scanf("%s", word2);
    LettereSuEntrambeParole(word, word2);
    PiuVocali(word, word2);
    PiuConsonanti(word, word2);
    return 0;
}