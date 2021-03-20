#include <stdio.h>

#include "board.h"
#include "filem.h"

int main() {
    Board b;
    int p=0;
    int d=0;
    char f[21] = {'a','w','w','w','e','e','w','w','w','e','e','e','e','e','w','e','w','w','w','e','e'};
    char e[21] = {'a','w','w','w','e','e','w','w','w','e','e','e','e','e','w','e','w','w','w','e','e'};
    for (int i = 0; i < B_ROWS; i++)
    {
        for (int j = 0; j < B_COLUMNS; j++)
        {
            if (j<3){
                if (f[p]!='w') {
                    b.data[i][j] = 1;
                }else{
                    b.data[i][j] = 0;
                }
                p++;
            }else if (j>7){
                if (e[d]!='w') {
                    b.data[i][j] = 1;
                }else{
                    b.data[i][j] = 0;
                }
                d++;
            } else{
                b.data[i][j] = 0;
            }

        }
    }

    printBoard(b);
    char c[21] = {'a','w','w','w','e','e','w','w','w','e','e','e','e','e','w','e','e','w','e','w','e'};
    saveForm(1, c);

    char *tempForm = loadForm(1);
    for (int i = 0; i < 21; i++)
    {
        printf("%c", tempForm[i]);
    }
}