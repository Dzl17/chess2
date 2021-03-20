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
 * Devuelve la id de la pieza en la posición requerida.
 * @param board Tablero
 * @param x X de la pieza
 * @param y Y de la pieza
 * @return ID de la pieza
 */
int locateId(Board board, int x, int y);

#endif //CHESS2_BOARD_H
