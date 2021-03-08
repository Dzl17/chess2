#ifndef CHESS2_BOARD_H
#define CHESS2_BOARD_H

#define B_ROWS 11 //Por si se cambia el tamaño
#define B_COLUMNS 7

typedef struct {
    int data[B_ROWS][B_COLUMNS];
    int time, turn;
} Board;



#endif //CHESS2_BOARD_H
