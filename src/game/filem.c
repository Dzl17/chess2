#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "filem.h"

char *conc(const char *a, const char *b, const char *c);

void saveForm(int id, char *code)
{
    if (id >= 10) {
        printf("Error: ID inválida (mayor que 10).\n");
        return;
    }
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
    if (id >= 10) {
        printf("Error: ID inválida (mayor que 10).\n");
        return NULL;
    }
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

void saveGame(int turn, int nexus1hp, int nexus2hp, int pieces[24][4])
{
    FILE *filew = fopen("..\\data\\save.txt", "w"); // Si el archivo no existe, se crea
    fprintf(filew, "%d %d %d 0 \n", turn, nexus1hp, nexus2hp); // Turno actual y vidas de nexos
    for (int i = 0; i < 24; i++) {
        fprintf(filew, "%d %d %d %d \n", pieces[i][0], pieces[i][1], pieces[i][2], pieces[i][3]);
    }
    fclose(filew);
}

int** loadGame()
{
    FILE *filer = fopen("..\\data\\save.txt", "r");
    if (filer == NULL) return NULL;
    int **data = malloc(sizeof(int*) * 25); // Datos a devolver
    for (int i = 0; i < 25; i++) data[i] = malloc(sizeof(int) * 4);
    char c; // Caracter leído
    int i = 0; // Entrada del return
    int j = 0; // Sub-entrada del return
    int intbuffer[4]; // Buffer para ints de más de 1 dígito
    for (int k = 0; k < 4; k++) intbuffer[k] = -1; // Se llena de -1 para poder comprobar la longitud del número
    int n = 0; // Contador de dígitos para el buffer
    while ((c = (char) fgetc(filer)) != EOF) {
        if (c != '\n') {
            if (c == ' ') { // Cambio de columna
                int digits = 0; // Comprobador de dígitos
                for (int k = 0; k < 4; k++) if (intbuffer[k] != -1) digits++; // Número de dígitos del número
                int tempNum = 0;
                for (int k = 0; k < digits; k++) tempNum += intbuffer[k] * (int) pow(10, digits - k - 1); // Calcular el número
                data[i][j] = tempNum; // Introducir el número
                j++; // Pasar a siguiente columna
                for (int k = 0; k < 4; k++) intbuffer[k] = -1; // Resetear el buffer
                n = 0;
            } else { // Cambio de dígito
                intbuffer[n] = c - '0';
                n++;
            }
        } else {
            int digits = 0; // Comprobador de dígitos
            for (int k = 0; k < 4; k++) if (intbuffer[k] != -1) digits++; // Número de dígitos del número
            int tempNum = 0;
            for (int k = 0; k < digits; k++) tempNum += intbuffer[k] * (int) pow(10, digits - k - 1); // Calcular el número
            data[i][j] = tempNum; // Introducir el número
            i++;
            j = 0;
            n = 0;
            for (int k = 0; k < 4; k++) intbuffer[k] = -1; // Resetear el buffer
        }
    }
    fclose (filer);
    return data;
}

/**
 * Devuelve la unión de 3 strings.
 */
char *conc(const char *a, const char *b, const char *c) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);
    size_t clen = strlen(c);
    char *res = malloc(alen + blen + clen + 1);
    if (res) {
        strcpy(res, a);
        strcpy(res + alen, b);
        memcpy(res + alen + blen, c, clen + 1);
    }
    return res;
}