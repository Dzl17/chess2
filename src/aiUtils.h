#ifndef CHESS2_AIUTILS_H
#define CHESS2_AIUTILS_H

#include "content.h"

/*
 * ELEGIR QUÉ MOVER:
 * - Guardar todas las posibles combinaciones de pieza-casilla a mover
 * - Mover hacia el nexo (evaluar dirección)
 * - Grupos de prioridad: elegir al azar una pieza de un grupo de columnas
 * - Si una pieza enemiga tiene poca vida, mover hacia ella para eliminarla
 *
 * ELEGIR QUÉ ATACAR:
 * - Guardar todas las posibles combinaciones de pieza-casilla a atacar
 * - Ver si se puede matar; si se puede, hacerlo. Podemos poner prioridad entre piezas
 * - Si no puede matar a nadie, sacar qué ataque da más ventaja de estadísticas
 * - Si no hay piezas atacables o no hay mucha ventaja, mover pieza
 * - Prioridad: MATAR NEXO -> MATAR PIEZA -> ATACAR NEXO -> ATACAR ENEMIGO AMENAZANTE-> ATACAR PIEZA (si hay ventaja) / Mover
 *
 * ESTRATEGIA ESPECÍFICA
 * - Colocar los tanques para defender el nexo (atacan si hay enemigos alcanzables)
 *
 * TODO:
 * - aiMovePiece() debe gestionar los cambios de estado de la pieza movida de Choosing/Idle a Moving/Attacking
 *   y el cambio de turno
 */

void aiMovePiece(VcPieces& pieces, Game *game);

#endif //CHESS2_AIUTILS_H
