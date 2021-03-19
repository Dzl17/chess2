#ifndef CHESS2_BOARD_H
#define CHESS2_BOARD_H

#define B_ROWS 7 //Por si se cambia el tamaño
#define B_COLUMNS 11

typedef struct {
    int data[B_ROWS][B_COLUMNS];
    int time, turn;
} Board;

/**
 * Imprime el estado actual de el tablero.
 * @param board Datos de la tabla
 */
void printBoard(Board board);

#endif //CHESS2_BOARD_H
