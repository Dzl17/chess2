#ifndef CHESS2_BOARD_H
#define CHESS2_BOARD_H

#define B_ROWS 7 //Por si se cambia el tamaño
#define B_COLUMNS 11

/*
 * APUNTES TABLERO
 * -Posiciones inmutables: [3][0] y [3][10] (nexos)
 * -
 */

typedef struct {
    int data[B_ROWS][B_COLUMNS];
    int time, turn;
} Board;

/**
 * Imprime el estado actual de el tablero.
 * @param board Datos de la tabla
 */
void printBoard(Board board);

/**
 * Devuelve la x/y de la pieza requerida.
 * @param board Tablero
 * @param id Id de la pieza necesitada
 * @return Puntero a array con x e y.
 */
int * locateId(Board board, int id);

#endif //CHESS2_BOARD_H
