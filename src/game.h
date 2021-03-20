#ifndef CHESS2_GAME_H
#define CHESS2_GAME_H

#define B_ROWS 7 //Por si se cambia el tamaño
#define B_COLUMNS 11

#include "tempiece.h"

typedef struct {
    TestPiece pieces[24];
    int data[B_ROWS][B_COLUMNS];
    int time, turn;
} Game;

void updatePiece(Game *game, const char *origin, const char *destiny);
void movePiece(TestPiece *piece, Game *game, int originX, int originY, int destinyX, int destinyY);
void attackPiece(TestPiece *piece1, TestPiece *piece2, Game *game);

/**
 * Imprime el estado actual de el tablero.
 * @param board Datos de la tabla
 */
void printBoard(Game game);

/**
 * Devuelve la id de la pieza en la posición requerida.
 * @param board Tablero
 * @param x X de la pieza
 * @param y Y de la pieza
 * @return ID de la pieza
 */
int locateId(Game game, int x, int y);

#endif //CHESS2_GAME_H
