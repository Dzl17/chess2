#include <stdio.h>

#include "game.h"

void updatePiece(TestPiece *piece, Board *board, const char *origin, const char *destiny)
{
    int team = piece->id <= 12 ? 0 : 1; // 0 equipo "blanco", 1 equipo "negro"
    int originX = origin[0] - 'a';
    int originY = origin[1] - '0';
    int destinyX = destiny[0] - 'a';
    int destinyY = destiny[1] - '0';
    int destinyCode = board->data[destinyX][destinyY];
    if (destinyCode == 0) {
        movePiece(piece, board, originX, originY, destinyX, destinyY);
    }
    else if ((destinyCode <= 12 && team == 1) || (destinyCode >= 12 && team == 0)) {
        //attackPiece();
    }
    else {
        printf("La casilla está ocupada por una pieza propia.\n");
        return;
    }
}

void movePiece(TestPiece *piece, Board *board, int originX, int originY, int destinyX, int destinyY)
{
    switch (pieceType(piece)) {
        case 0: // Lancero
            board->data[originX][originY] = 0;
            board->data[destinyX][destinyY] = piece->id;
            break;
        case 1: // Mago
            board->data[originX][originY] = 0;
            board->data[destinyX][destinyY] = piece->id;
            break;
        case 2: // Asesino
            board->data[originX][originY] = 0;
            board->data[destinyX][destinyY] = piece->id;
            break;
        case 3: // Golem
            if (canMove(piece, originX, originY, destinyX, destinyY)) {
                board->data[originX][originY] = 0;
                board->data[destinyX][destinyY] = piece->id;
            } else {
                printf("Movimiento ilegal para Golem\n");
            }
            break;
    }
}

void attackPiece(TestPiece *piece1, TestPiece *piece2, Board *board)
{

}