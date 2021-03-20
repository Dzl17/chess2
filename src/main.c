#include <stdio.h>

#include "game.h"
#include "filem.h"

void clearStdin();

int main() {
    Game game;
    startGame(&game, 1, 1);
    printBoard(game);
    char c1[2];
    char c2[2];
    scanf("%c%c", &c1[0], &c1[1]);
    printf("%c%c\n", c1[0], c1[1]);
    clearStdin();
    scanf("%c%c", &c2[0], &c2[1]);
    printf("%c%c\n", c2[0], c2[1]);
    clearStdin();
    printf("ESCANEADO\n");
    updatePiece(&game, c1, c2);
    printf("ACTUALIZADO\n");
    printBoard(game);

    /*
    TestPiece pi[24] = {{1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}, {7, 10}, {8, 10}, {9, 10}, {10, 10}, {11, 10},
                   {12, 10}, {13, 10}, {14, 10}, {15, 10}, {16, 10}, {17, 10}, {18, 10}, {19, 10}, {20, 10}, {21, 10},
                   {22, 10}, {23, 10}, {24, 10}};
                   */
}

void clearStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}