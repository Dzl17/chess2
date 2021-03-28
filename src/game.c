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

    for (int i = 0; i < 24; i++) game->pieces[i] = (Piece) {i + 1, 10};
    game->pieces[24]=(Piece) {25, NEXUS_HP};
    game->pieces[25]=(Piece) {26, NEXUS_HP};
    int s = 1;      // Lanceros
    int w = 5;      // Magos
    int a = 8;      // Asesinos
    int g = 11;     // Golems

    for (int i = 0; i < B_ROWS; i++) { // Lado izquierdo
        for (int j = 0; j < 3; j++) {
            char unit = form1[3 * i + j];
            if (unit == 's')      game->data[i][j] = s++;
            else if (unit == 'w') game->data[i][j] = w++;
            else if (unit == 'a') game->data[i][j] = a++;
            else if (unit == 'g') game->data[i][j] = g++;
            else if (unit == 'e') game->data[i][j] = 0;
            else if (unit == 'N') game->data[i][j] = 25;
        }
    }

    s = 13;      // Lanceros
    w = 17;      // Magos
    a = 20;      // Asesinos
    g = 23;     // Golems
    for (int i = 0; i < B_ROWS; i++) { // Lado derecho
        for (int j = 2; j >= 0; j--) {
            char unit = form2[3 * i + 2 - j];
            if (unit == 's')      game->data[i][j+8] = s++;
            else if (unit == 'w') game->data[i][j+8] = w++;
            else if (unit == 'a') game->data[i][j+8] = a++;
            else if (unit == 'g') game->data[i][j+8] = g++;
            else if (unit == 'e') game->data[i][j+8] = 0;
            else if (unit == 'N') game->data[i][j+8] = 26;
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
    // Extraer y evaluar posiciones
    int originX = origin[1] - '0' - 1;
    int originY = origin[0] - 'a';
    int destinyX = destiny[1] - '0' - 1;
    int destinyY = destiny[0] - 'a';

    if (invalidPositions(originX, originY, destinyX, destinyY)) {
        printf("Posicion no valida.\n");
        return 0;
    }

    // Localizar pieza, si la hay
    int id = locateId(*game, originX, originY); // ID de la pieza en la posición de origen
    if (id == 0) { // Si no hay pieza
        printf("Casilla vacia.\n");
        return 0;
    } else if (id >= 25) { // Si la pieza es un nexo (IDs 25 y 26)
        printf("No se puede mover el nexo.\n");
        return 0;
    }
    Piece *piece = NULL; // Puntero a pieza objetivo
    for (int i = 0; i < 24; i++) { // Encontrar y asignar pieza objetivo
        if (game->pieces[i].id == id) {
            if (game->pieces[i].hp > 0) piece = &game->pieces[i]; // Asignar si la pieza está "viva"
            break;
        }
    }

    // Evaluar equipo y actualizar el estado de las piezas
    int team = piece->id <= 12 ? 0 : 1; // 0 equipo izquierdo, 1 equipo derecho
    int destinyCode = game->data[destinyX][destinyY]; // Comprobar estado de la casilla objetivo

    if (destinyCode == 0 && team == game->turn % 2) { // Casilla vacía y pieza aliada
        if (movePiece(piece, game, originX, originY, destinyX, destinyY)) {
            printf("Pieza movida correctamente.\n");
            return 1;
        }
        else return 0;
    }
    else if (team != game->turn % 2) { // Mover a pieza enemiga
        printf("Esa no es una de tus piezas.\n");
        return 0;
    }
    else if (((destinyCode <= 12 || destinyCode == 24) && team == 1) || ((destinyCode >= 12) && team == 0)) { // Atacar a pieza enemiga
        // Localizar pieza enemiga
        Piece *enemypiece = NULL; // Puntero a pieza enemiga
        int enemyId = locateId(*game, destinyX, destinyY);
        for (int i = 0; i < 26; i++) { // Encontrar y asignar pieza enemiga
            if (game->pieces[i].id == enemyId) {
                if (game->pieces[i].hp > 0) {
                    enemypiece = &game->pieces[i]; // Asignar si la pieza está "viva"
                    break;
                }
            }
        }

        int attackResult = attackPiece(enemypiece);
        if (attackResult == 0) {
            if (attackPiece(piece)) movePiece(enemypiece, game, originX, originY, destinyX, destinyY); // Contraataque
            printf("Ataque realizado.\n");
        } else if (attackResult == 1) {
            movePiece(piece, game, originX, originY, destinyX, destinyY);
            printf("Pieza eliminada.\n");
        } else if (attackResult == 2) {
            if (enemypiece->id == 25) game->nexus1hp -= 5;
            else if (enemypiece->id == 26) game->nexus2hp -= 5;
            printf("Nexo atacado.\n");
        }
        return 1;
    }
    else { // Pieza propia
        printf("La casilla esta ocupada por una pieza propia.\n");
        return 0;
    }
}

int movePiece(Piece *piece, Game *game, int originX, int originY, int destinyX, int destinyY)
{
    if (canMove(piece, originX, originY, destinyX, destinyY)) {
        game->data[originX][originY] = 0;
        game->data[destinyX][destinyY] = piece->id;
        return 1;
    } else {
        printf("Movimiento ilegal\n");
        return 0;
    }
}

int attackPiece(Piece *piece)
{
    piece->hp -= 5; // TODO: cambiar por daño de pieza
    if (piece->hp < 1 && piece->id <= 24) return 1; // Pieza eliminada
    else if (piece->id > 24) return 2; // Nexo golpeado
    else if (piece->hp < 1 && piece->id > 24) return 3; // Nexo eliminado
    else return 0; // Pieza golpeada
}

void printBoard(Game game)
{
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 11; j++) {
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