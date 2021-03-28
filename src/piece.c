#include <stdlib.h>
#include <stdio.h>

#include "piece.h"

int pieceType(Piece *piece)
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

char pieceLetter(int id)
{
    if ((id >= 1 && id <= 4) || (id >= 13 && id <= 16)) {
        return 's';
    } else if ((id >= 5 && id <= 7) || (id >= 17 && id <= 19)) {
        return 'w';
    } else if ((id >= 8 && id <= 10) || (id >= 20 && id <= 22)) {
        return 'a';
    } else if ((id >= 11 && id <= 12) || (id >= 23 && id <= 24)){
        return 'g';
    } else if (id > 24) {
        return 'N';
    } else {
        return ' ';
    }
}

int getDamage(int id)
{
    if ((id >= 1 && id <= 4) || (id >= 13 && id <= 16)) {
        return 5; // Daño lancero
    } else if ((id >= 5 && id <= 7) || (id >= 17 && id <= 19)) {
        return 5; // Daño mago
    } else if ((id >= 8 && id <= 10) || (id >= 20 && id <= 22)) {
        return 5; // Daño asesino
    } else {
        return 5; // Daño golem
    }
}

int canMove(Piece *piece, int originX, int originY, int destinyX, int destinyY)
{
    if (destinyX < 0 || destinyX > 6 || destinyY < 0 || destinyY > 10) return 0;
    if (piece->id < 0) return 0;
    switch (pieceType(piece)) {
        case 0: // Lancero - s
            if (piece->id <= 12) return (destinyX == originX + 1 || destinyX == originX + 2) && originY == destinyY;
            else return (destinyX == originX - 1 || destinyX == originX - 2) && originY == destinyY;
        case 2: // Asesino - a

        case 1: // Mago - w
        case 3: // Golem - g
            if ((abs(originX - destinyX) == 1 && abs(originY - destinyY) == 0) ||
                (abs(originY - destinyY) == 1 && abs(originX - destinyX) == 0) ||
                (abs(originX - destinyX) == 1 && abs(originY - destinyY) == 1)) return 1;
            else return 0;
        default:
            return 0;
    }
}

int canAttack(Piece *piece, Piece *enemyPiece, int originX, int originY, int destinyX, int destinyY)
{
    if (destinyX < 0 || destinyX > 6 || destinyY < 0 || destinyY > 10) return 0;
    if (piece->id < 0) return 0;

    int team = piece->id <= 12 || piece->id == 25 ? 0 : 1;
    int enemyTeam = enemyPiece->id <= 12 || enemyPiece->id == 25 ? 0 : 1;
    if (team == enemyTeam) return 0;
    switch (pieceType(piece)) {
        case 0: // Lancero - s
            if (piece->id <= 12) return destinyX == originX + 1 && (abs(destinyY - originY) <= 1);
            else return destinyX == originX - 1 && (abs(destinyY - originY) <= 1);
        case 1: // Mago - w

        case 2: // Asesino - a
        case 3: // Golem - g
            return canMove(piece, originX, originY, destinyX, destinyY);
        default:
            return 0;
    }
}

