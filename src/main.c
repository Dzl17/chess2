#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "filem.h"

void clearStdin();

void choseForm(int f)
{
    printf("Formacion %d:\n",f);
    char *form3 = loadForm(f);
    int seg=0;
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 3; j++)
        {
            switch (form3[3 * i + j]) {
                case 's':
                    printf("%c|",form3[seg]);
                    break;
                case 'w':
                    printf("%c|",form3[seg]);
                    break;
                case 'a':
                    printf("%c|",form3[seg]);
                    break;
                case 'g':
                    printf("%c|",form3[seg]);
                    break;
                case 'e':
                    printf(" |");
                    break;
            }
            seg++;
        }
        printf("\n"); // Formateo
    }
    printf("\n");
}

int main() {
    choseForm(1);
    choseForm(3);
    Game game;
    char form;
    printf("Escoger formacion: ");
    scanf("%d", &form);
    clearStdin();
    printf("\n");
    startGame(&game, form, 1);
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
