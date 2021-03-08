#ifndef CHESS2_FILEM_H
#define CHESS2_FILEM_H

#define FORM_LENGTH 21 //Tamaño del string de formaciones

//IMPORTANTE: intentar "aislar" este módulo, no utilizar la estructura Board ni nada parecido
//Probablemente haya que cambiar la forma de pasar arrays de loadGame()

void saveForm(int id, char *code); // Guardar formación actual
const char * loadForm(int id); // Leer formación, TODO 4 IDs en total?

void saveGame(int time, int turn, int pieces[][4]); // Guardar estado del juego
int** loadGame(); // Cargar estado del juego (entrada 0 son los datos extras, las siguientes son piezas)

#endif //CHESS2_FILEM_H
