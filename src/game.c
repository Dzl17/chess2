#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "filem.h"

/**
 * Comprueba si las casillas introducidas son válidas.
 * @return 1 si son inválidas
 */
int invalidPositions(int x1, int y1, int x2, int y2);

void startGame(Game *game, int f1, int f2)
{
    game->time = 0;
    game->turn = 0;
    game->nexus1hp = NEXUS_HP;
    game->nexus2hp = NEXUS_HP;
    char *form1 = loadForm(f1);
    char *form2 = loadForm(f2);

    for (int i = 0; i < 24; i++) game->pieces[i] = (TestPiece) {i+1,10};

    int s = 1;      // Lanceros
    int w = 5;      // Magos
    int a = 8;      // Asesinos
    int g = 11;     // Golems
    for (int i = 0; i < B_ROWS; i++) { // Lado izquierdo
        for (int j = 0; j < 3; j++) {
            switch (form1[3 * i + j]) {
                case 's':
                    game->data[i][j] = s++;
                    break;
                case 'w':
                    game->data[i][j] = w++;
                    break;
                case 'a':
                    game->data[i][j] = a++;
                    break;
                case 'g':
                    game->data[i][j] = g++;
                    break;
                case 'e':
                    game->data[i][j] = 0;
                    break;
            }
        }
    }
    s = 13;      // Lanceros
    w = 17;      // Magos
    a = 20;      // Asesinos
    g = 23;     // Golems
    for (int i = 0; i < B_ROWS; i++) { // Lado derecho
        for (int j = 2; j >= 0; j--) {
            switch (form2[3 * i + 2 - j]) {
                case 's':
                    game->data[i][j+8] = s++;
                    break;
                case 'w':
                    game->data[i][j+8] = w++;
                    break;
                case 'a':
                    game->data[i][j+8] = a++;
                    break;
                case 'g':
                    game->data[i][j+8] = g++;
                    break;
                case 'e':
                    game->data[i][j+8] = 0;
                    break;
            }
        }
    }
    for (int i = 0; i < B_ROWS; i++) { // Lado central
        for (int j = 3; j < 8; j++) {
            game->data[i][j] = 0;
        }
    }
    free(form1);
    free(form2);
}

int updatePiece(Game *game, const char *origin, const char *destiny)
{
    int originX = origin[1] - '0' - 1;
    int originY = origin[0] - 'a';
    int destinyX = destiny[1] - '0' - 1;
    int destinyY = destiny[0] - 'a';

    if (invalidPositions(originX, originY, destinyX, destinyY)) {
        printf("Posicion no valida.\n");
        return 0;
    }

    int id = locateId(*game, originX, originY); // ID de la pieza en la posición de origen
    if (id == 0) { // Si no hay pieza
        printf("Casilla vacia.\n");
        return 0;
    }

    TestPiece *piece = NULL; // Puntero a pieza objetivo
    for (int i = 0; i < 22; i++) { // Encontrar y asignar pieza objetivo
        if (game->pieces[i].id == id) {
            if (game->pieces[i].hp > 0) piece = &game->pieces[i]; // Asignar si la pieza está "viva"
            break;
        }
    }

    int team = piece->id <= 12 ? 0 : 1; // 0 equipo "blanco", 1 equipo "negro"
    int destinyCode = game->data[destinyX][destinyY]; // Comprobar estado de la casilla objetivo

    if (destinyCode == 0 && team == game->turn%2) { // Casilla vacía
        movePiece(piece, game, originX, originY, destinyX, destinyY);
        return 1;
    }
    else if(team != game->turn%2){
        printf("Esa no es una de tus piezas.\n");
        return 0;
    }
    else if ((destinyCode <= 12 && team == 1) || (destinyCode >= 12 && team == 0)) { // Pieza enemiga

        TestPiece *enemypiece = NULL; // Puntero a pieza enemiga
        int enemId=locateId(*game, destinyX, destinyY);

        for (int i = 0; i < 22; i++) { // Encontrar y asignar pieza enemiga
            if (game->pieces[i].id == enemId) {
                if (game->pieces[i].hp > 0) {
                    enemypiece = &game->pieces[i]; // Asignar si la pieza está "viva"
                }
                break;
            }
        }

        int suc=attackPiece(piece,enemypiece,game);
        if (suc) {
            movePiece(piece, game, originX, originY, destinyX, destinyY);
            return 1;
        }
    }
    else {
        printf("La casilla esta ocupada por una pieza propia.\n");
        return 0;
    }
}

void movePiece(TestPiece *piece, Game *game, int originX, int originY, int destinyX, int destinyY)
{
    if (destinyX == 3 && ((destinyY == 0) || destinyY == 10)) {
        printf("Casilla de nexo\n"); // TODO comprobar en updatePiece()
    }
    else if (canMove(piece, originX, originY, destinyX, destinyY)) {
        game->data[originX][originY] = 0;
        game->data[destinyX][destinyY] = piece->id;
    } else {
        printf("Movimiento ilegal\n");
    }
}

int attackPiece(TestPiece *piece1, TestPiece *piece2, Game *game)
{
    piece2->hp=piece2->hp-15;
    if (piece2->hp<1) return 1;
    else return 0;
}

void printBoard(Game game)
{
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 11; j++)
        {
            int pieceCode = game.data[i][j];
            printf("%c|", pieceLetter(pieceCode));
            //printf("%d|", pieceCode);
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

int invalidPositions(int x1, int y1, int x2, int y2)
{
    return x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 > 6 || y1 > 10 || x2 > 6 || y2 > 10;
}