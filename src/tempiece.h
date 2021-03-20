#ifndef CHESS2_TEMPIECE_H
#define CHESS2_TEMPIECE_H

#include "board.h"

typedef struct {
    int id, hp;
} TestPiece;

int pieceType(TestPiece *piece);
int canMove(TestPiece *piece, int originX, int originY, int destinyX, int destinyY);

#endif //CHESS2_TEMPIECE_H
