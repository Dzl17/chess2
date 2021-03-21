#ifndef CHESS2_TEMPIECE_H
#define CHESS2_TEMPIECE_H

typedef struct {
    int id, hp;
} TestPiece;

/**
 * Devuelve el tipo de pieza.
 * @param piece Pieza requerida
 * @return ID 0-3 de la pieza
 */
int pieceType(TestPiece *piece);

/**
 * Devuelve si se puede mover una pieza a una posición objetivo
 * @param piece Pieza a mover
 * @param originX X origen
 * @param originY Y origen
 * @param destinyX X destino
 * @param destinyY Y destino
 * @return
 */
int canMove(TestPiece *piece, int originX, int originY, int destinyX, int destinyY);

#endif //CHESS2_TEMPIECE_H
