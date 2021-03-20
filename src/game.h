#ifndef CHESS2_GAME_H
#define CHESS2_GAME_H

#include "tempiece.h"

typedef struct {
    Board board;
    TestPiece pieces[24];
} Game;

void updatePiece(Game *game, const char *origin, const char *destiny);
void movePiece(TestPiece *piece, Board *board, int originX, int originY, int destinyX, int destinyY);
void attackPiece(TestPiece *piece1, TestPiece *piece2, Board *board);

#endif //CHESS2_GAME_H
