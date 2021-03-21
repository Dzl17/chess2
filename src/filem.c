#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filem.h"

char *conc(const char *a, const char *b, const char *c);

void saveForm(int id, char *code)
{
    char intBuffer[12]; //Pasa la ID a un string
    sprintf(intBuffer, "%d", id);
    FILE *filew = fopen(conc("..\\data\\form", intBuffer, ".txt"), "w"); // Si el archivo no existe, se crea
    for (int i = 0; i < FORM_LENGTH; i++) {
        fprintf(filew, "%c", code[i]);
    }
    fclose(filew);
}

char * loadForm(int id) //TODO NECESARIO LIBERAR PUNTERO DEVUELTO -> free((char*) c)
{
    char intBuffer[12]; //Pasa la ID a un string
    sprintf(intBuffer, "%d", id);
    FILE *filer = fopen(conc("..\\data\\form", intBuffer, ".txt"), "r");
    if (filer == NULL) return NULL;
    char *form = malloc(21);
    char c;
    int i = 0;
    while ((c = (char) fgetc(filer)) != EOF) {
        form[i++] = c;
    }
    fclose(filer);
    return form;
}

void saveGame(int time, int turn, int pieces[][4])
{

}

int** loadGame()
{

}

/**
 * Devuelve la unión de 3 strings.
 * @param a String 1
 * @param b String 2
 * @param c String 3
 * @return String unido
 */
char *conc(const char *a, const char *b, const char *c) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);
    size_t clen = strlen(c);
    char *res = malloc(alen + blen + clen + 1);
    if (res) {
        strcpy(res, a); //TODO cambiar por memcpy?
        strcpy(res + alen, b);
        memcpy(res + alen + blen, c, clen + 1);
    }
    return res;
}