#include <stdlib.h>

#include "tempiece.h"

int pieceType(TestPiece *piece)
{

    return 3; // TODO esqueleto
    if ((piece->id >= 1 && piece->id <= 4) || (piece->id >= 13 && piece->id <= 16)) {
        return 0;
    } else if ((piece->id >= 5 && piece->id <= 7) || (piece->id >= 17 && piece->id <= 19)) {
        return 1;
    } else if ((piece->id >= 8 && piece->id <= 10) || (piece->id >= 20 && piece->id <= 22)) {
        return 2;
    } else {
        return 3;
    }
}

int canMove(TestPiece *piece, int originX, int originY, int destinyX, int destinyY)
{
    if (destinyX < 0 || destinyX > 6 || destinyY < 0 || destinyY > 10) return 0;
    switch (pieceType(piece)) {
        case 0: // Lancero

        case 2: // Asesino

        case 1: // Mago
        case 3: // Golem
            if ((abs(originX - destinyX) == 1 && abs(originY - destinyY) == 0) ||
                (abs(originY - destinyY) == 1 && abs(originX - destinyX) == 0) ||
                (abs(originX - destinyX) == 1 && abs(originY - destinyY) == 1)) return 1;
            else return 0;
    }
}