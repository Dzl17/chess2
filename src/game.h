#ifndef CHESS2_GAME_H
#define CHESS2_GAME_H

#define B_ROWS 7 //Por si se cambia el tamaño
#define B_COLUMNS 11
#define NEXUS_HP 100

#include "tempiece.h"

typedef struct {
    TestPiece pieces[24];
    int data[B_ROWS][B_COLUMNS];
    int time, turn;
    int nexus1hp, nexus2hp; // Vidas de los nexos
} Game;

/**
 * Carga el juego.
 * @param game Puntero a juego a cargar
 * @param f1 ID de formación 1
 * @param f2 ID de formación 2
 */
void startGame(Game *game, int f1, int f2);

/**
 * Actualiza el estado de una pieza.
 * @param game Game base
 * @param origin Coordenadas de origen
 * @param destiny Coordenadas de destino
 */
int updatePiece(Game *game, const char *origin, const char *destiny);

/**
 * Mueve la pieza a una casilla introducida, si es posible.
 * @param piece Pieza a mover
 * @param game Game base
 * @param originX X origen
 * @param originY Y origen
 * @param destinyX X destino
 * @param destinyY Y destino
 */
void movePiece(TestPiece *piece, Game *game, int originX, int originY, int destinyX, int destinyY);
int attackPiece(TestPiece *piece1, TestPiece *piece2, Game *game);

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
