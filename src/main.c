#include <stdio.h>

#include "board.h"
#include "filem.h"

int main() {
    Board b;
    for (int i = 0; i < B_ROWS; i++)
    {
        for (int j = 0; j < B_COLUMNS; j++)
        {
            b.data[i][j] = i + j;
        }
    }
    b.data[2][6] = 0;
    b.data[2][2] = 0;
    b.data[1][6] = 0;
    b.data[0][3] = 0;
    printBoard(b);
    char c[21] = {'a','w','w','w','e','e','w','w','w','e','e','e','e','e','w','e','e','w','e','w','e'};
    saveForm(1, c);

    char *tempForm = loadForm(1);
    for (int i = 0; i < 21; i++)
    {
        printf("%c", tempForm[i]);
    }
}