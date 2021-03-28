#ifndef CHESS2_TEMPIECE_H
#define CHESS2_TEMPIECE_H

typedef struct {
    int id, hp;
} Piece;

/**
 * Devuelve el tipo de pieza.
 * @param piece Pieza requerida
 * @return ID 0-3 de la pieza
 */
int pieceType(Piece *piece);

/**
 * Devuelve el caracter asignado a la pieza.
 * @param id Id de la pieza
 * @return Caracter
 */
char pieceLetter(int id);

/**
 * Devuelve si se puede mover una pieza a una posición objetivo
 * @param piece Pieza a mover
 * @param originX X origen
 * @param originY Y origen
 * @param destinyX X destino
 * @param destinyY Y destino
 * @return Resultado del cálculo
 */
int canMove(Piece *piece, int originX, int originY, int destinyX, int destinyY);

/**
 * Devuelve si una pieza puede atacar la posición objetivo.
 * @param piece Pieza atacante
 * @param originX X origen
 * @param originY Y origen
 * @param destinyX X destino
 * @param destinyY Y destino
 * @return Resultado del cálculo
 */
int canAttack(Piece *piece, int originX, int originY, int destinyX, int destinyY);

#endif //CHESS2_TEMPIECE_H
