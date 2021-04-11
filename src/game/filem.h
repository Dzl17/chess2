#ifndef CHESS2_FILEM_H
#define CHESS2_FILEM_H

#define FORM_LENGTH 21 // Tamaño del string de formaciones

// IMPORTANTE: intentar "aislar" este módulo, no utilizar la estructura Board ni nada parecido

/**
 * Guarda una formación en un archivo.
 * @param id Id del archivo
 * @param code Array de la formación
 */
void saveForm(int id, char *code);

/**
 * Devuelve una formacion guardada en un archivo.
 * @param id Id del archivo
 * @return Puntero al array de la formación
 */
char *loadForm(int id); //TODO 4 IDs en total?


/**
 * Guarda en un archivo el estado del juego.
 * @param turn Turno de juego
 * @param pieces Estado de las piezas (id,vida,x,y)
 */
void saveGame(int turn, int nexus1hp, int nexus2hp, int pieces[24][4]);

/**
 * Devuelve un array con el estado del juego.
 * @return Array de estado (entrada 0 -> datos, entradas 1+ -> piezas)
 */
int **loadGame();

#endif //CHESS2_FILEM_H
