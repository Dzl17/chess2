#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "filem.h"

void clearStdin();
void halfBoard(char* espaces);
void chooseForm(int f);

int main() {
    printf("MENU PRINCIPAL: \n");
    printf("1) Jugar en local: \n");
    printf("2) Crear una formacion: \n");
    int option;
    printf("Introduzca opcion: ");
    scanf("%d", &option);
    clearStdin();
    if (option == 1) {
        chooseForm(1);
        chooseForm(3);
        Game game;
        char form;
        printf("Escoger formacion: ");
        scanf("%d", &form);
        clearStdin();
        printf("\n");
        startGame(&game, form, 1);
        system("cls"); // Para consola
        printf("Juego iniciado.\n\n");
        printBoard(game);
        char c1[2];
        char c2[2];
        while (game.nexus1hp > 0 && game.nexus2hp > 0) {
            printf("%d:%d, T%d, %c\n", game.nexus1hp, game.nexus2hp, game.turn, game.turn % 2 ? 'D' : 'I');
            printf("Casilla origen: ");
            scanf("%c%c", &c1[0], &c1[1]);
            if (c1[0] == 'm') break;
            clearStdin();
            printf("Casilla destino: ");
            scanf("%c%c", &c2[0], &c2[1]);
            clearStdin();
            system("cls"); // Para consola
            int jugada = updatePiece(&game, c1, c2);
            if (jugada) {
                game.turn++;
            }
            printf("\n");
            printBoard(game);

        }
        printf("Partida terminada\n");
        printf("Gana el equipo %d\n",game.turn%2);
    } else if (option == 2) {
        printf("\n");
        char pieceArr[] = "ssssggwwwaaa";
        char spaces[] = "eeeeeeeeeeeeeeeeeeeee";

        char c1[2];
        int x;
        int y;
        int p = 0;
        while (p < 12) {
            halfBoard(spaces);
            printf("Donde quieres colocar %c\n", pieceArr[p]);
            scanf("%c%c", &c1[0], &c1[1]);
            clearStdin();
            x = c1[1] - '0' - 1;
            y = c1[0] - 'a';
            int pos = y + (x * 3);
            if (spaces[pos] == 'e' && (x >= 0 && x < 7) && (y >= 0 && y < 3)){
                spaces[pos] = pieceArr[p];
                p++;
            } else {
                printf("No se puede colocar en esa casilla\n");
            }
        }
        halfBoard(spaces);
        printf("Formacion terminada\n");
        saveForm(1, spaces);

    }

    /*
    Piece pi[24] = {{1, 10}, {2, 10}, {3, 10}, {4, 10}, {5, 10}, {6, 10}, {7, 10}, {8, 10}, {9, 10}, {10, 10}, {11, 10},
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

void halfBoard(char* espaces)
{
    int seg = 0;

    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 3; j++) {
            if (espaces[seg] == 'e') printf(" |");
            else printf("%c|",espaces[seg]);
            seg++;
        }
        printf("\n"); // Formateo
    }
    printf("     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("^ "); // Formateo
    }

    printf("\n     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");
}

void chooseForm(int f)
{
    printf("Formacion %d:\n",f);
    char *form = loadForm(f);
    int seg = 0;
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 3; j++) {
            char unit = form[3 * i + j];
            if (unit == 'e') printf(" |");
            else if (unit == 'N') printf("N|");
            else if (unit == 's' || unit == 'w' || unit == 'a' || unit == 'g') printf("%c|", form[seg]);
            seg++;
        }
        printf("\n"); // Formateo
    }
    printf("     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("^ "); // Formateo
    }

    printf("\n     "); // Formateo
    for (int i = 0; i < 3; i++) {
        printf("%c ", 'a' + i);
    }
    printf("\n");
}
