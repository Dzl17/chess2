#ifndef CHESS2_GAME_H
#define CHESS2_GAME_H

#define B_ROWS 7 // Por si se cambia el tamaño
#define B_COLUMNS 11
#define NEXUS_HP 150 // Vida fija del nexo

#include "piece.h"

typedef struct {
    Piece pieces[26];
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
void startGame(Game *game, char *f1, char *f2);

/**
 * Actualiza el estado de una pieza.
 * @param game Game base
 * @param origin Coordenadas de origen
 * @param destiny Coordenadas de destino
 * @return Resultado del movimiento
 */
int updatePiece(Game *game, int originX, int originY, int destinyX, int  destinyY);

/**
 * Mueve la pieza a una casilla introducida, si es posible.
 * @param piece Pieza a mover
 * @param game Game base
 * @param originX X origen
 * @param originY Y origen
 * @param destinyX X destino
 * @param destinyY Y destino
 */
int movePiece(Piece *piece, Game *game, int originX, int originY, int destinyX, int destinyY);

/**
 * Ataca a una pieza.
 * @param piece Pieza atacada
 * @return Resultado del ataque: 0 = pieza golpeada, 1 = pieza eliminada, 2 = nexo golpeado, 3 = nexo eliminado
 */
int attackPiece(Piece *piece);

/**
 * Imprime el estado actual de el tablero.
 * @param board Datos de la tabla
 */
void printBoard(Game game);

/**
 * Imprime la vida de las piezas en el tablero.
 * @param game Datos de la tabla
 */
void printLifeBoard(Game game);

/**
 * Devuelve la id de la pieza en la posición requerida.
 * @param board Tablero
 * @param x X de la pieza
 * @param y Y de la pieza
 * @return ID de la pieza
 */
int locateId(Game game, int x, int y);

/**
 * Devuelve un array con la x y la y de la id requerida
 * @param board Tablero
 * @param ID de la pieza
 * @return x X de la pieza
 * @return y Y de la pieza
 */
int* getPiecePos(Game game, int id);
#endif //CHESS2_GAME_H
