#include <stdio.h>

#include "game.h"

void updatePiece(Game *game, const char *origin, const char *destiny)
{
    int originX = origin[0] - 'a';
    int originY = origin[1] - '0';
    int destinyX = destiny[0] - 'a';
    int destinyY = destiny[1] - '0';

    int id = locateId(game->board, originX, originY);
    TestPiece *piece = NULL;
    for (int i = 0; i < 22; i++) {
        if (game->pieces[i].id == id) {
            piece = &game->pieces[i];
            break;
        }
    }

    int team = piece->id <= 12 ? 0 : 1; // 0 equipo "blanco", 1 equipo "negro"
    int destinyCode = game->board.data[destinyX][destinyY];
    if (destinyCode == 0) {
        movePiece(piece, &(game->board), originX, originY, destinyX, destinyY);
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
    if (canMove(piece, originX, originY, destinyX, destinyY)) {
        board->data[originX][originY] = 0;
        board->data[destinyX][destinyY] = piece->id;
    } else {
        printf("Movimiento ilegal\n");
    }
}

void attackPiece(TestPiece *piece1, TestPiece *piece2, Board *board)
{

}