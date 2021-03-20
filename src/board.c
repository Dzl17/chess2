#include <stdio.h>

#include "board.h"

void printBoard(Board board)
{
    for (int i = 0; i < 7; i++) {
        printf("%d > |", i + 1);
        for (int j = 0; j < 11; j++)
        {
            int piece = board.data[i][j];
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

int * locateId(Board board, int x, int y)   //Buscar ID
{
    return board.data[x][y];
}