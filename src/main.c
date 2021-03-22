#include <stdio.h>
#include <stdlib.h>

#include "game.h"

void clearStdin();

int main() {
    Game game;
    startGame(&game, 1, 1);
    printBoard(game);
    char c1[2];
    char c2[2];
    while (game.nexus1hp > 0 && game.nexus2hp > 0) {
        printf("%d:%d, T%d\n", game.nexus1hp, game.nexus2hp, game.turn);
        printf("Casilla origen: ");
        scanf("%c%c", &c1[0], &c1[1]);
        clearStdin();
        printf("Casilla destino: ");
        scanf("%c%c", &c2[0], &c2[1]);
        if (c1[0] == 'm') break;
        clearStdin();
        int jugada = updatePiece(&game, c1, c2);
        //system("cls"); // Para consola
        if (jugada) {
            game.turn++;
        }
        printf("\n");
        printBoard(game);

    }
    /*
    TestPiece pi[24] = {{1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}, {7, 10}, {8, 10}, {9, 10}, {10, 10}, {11, 10},
                   {12, 10}, {13, 10}, {14, 10}, {15, 10}, {16, 10}, {17, 10}, {18, 10}, {19, 10}, {20, 10}, {21, 10},
                   {22, 10}, {23, 10}, {24, 10}};
                   */
    return 0;
}

void clearStdin()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}