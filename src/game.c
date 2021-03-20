#include <stdio.h>

#include "game.h"

void updatePiece(Game *game, const char *origin, const char *destiny)
{
    int originX = origin[0] - 'a';
    int originY = origin[1] - '0';
    int destinyX = destiny[0] - 'a';
    int destinyY = destiny[1] - '0';

    int id = locateId(*game, originX, originY);
    TestPiece *piece = NULL;
    for (int i = 0; i < 22; i++) {
        if (game->pieces[i].id == id) {
            piece = &game->pieces[i];
            break;
        }
    }

    int team = piece->id <= 12 ? 0 : 1; // 0 equipo "blanco", 1 equipo "negro"
    int destinyCode = game->data[destinyX][destinyY];
    if (destinyCode == 0) {
        movePiece(piece, game, originX, originY, destinyX, destinyY);
    }
    else if ((destinyCode <= 12 && team == 1) || (destinyCode >= 12 && team == 0)) {
        //attackPiece();
    }
    else {
        printf("La casilla está ocupada por una pieza propia.\n");
        return;
    }
}

void movePiece(TestPiece *piece, Game *game, int originX, int originY, int destinyX, int destinyY)
{
    if (canMove(piece, originX, originY, destinyX, destinyY)) {
        game->data[originX][originY] = 0;
        game->data[destinyX][destinyY] = piece->id;
    } else {
        printf("Movimiento ilegal\n");
    }
}

void attackPiece(TestPiece *piece1, TestPiece *piece2, Game *game)
{

}

void printBoard(Game game)
{
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 11; j++)
        {
            int piece = game.data[i][j];
            char tempChar;
            if (piece == 0) tempChar = ' ';
            else tempChar = 'p';
            printf("%c|", tempChar);
        }
        printf("\n"); // Formateo
    }

    printf("     "); // Formateo
    for (int i = 0; i < 11; i++) {
        printf("^ "); // Formateo
    }

    printf("\n     "); // Formateo
    for (int i = 0; i < 11; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");
}

int locateId(Game game, int x, int y)   //Buscar ID
{
    return game.data[x][y];
}