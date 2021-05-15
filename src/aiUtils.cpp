#include "aiUtils.h"
#include <map>

// Pasar posicion introducida a coordenadas de tablero
std::vector<Vec2> posToCoords(int x, int y);

// Posiciones disponibles, el flag de 'attack' coge las de ataque en vez de las de defensa
std::map<PieceSprite, std::vector<Vec2>> getAvailableSquares(VcPieces pieces, bool attack);

// Evaluar si hay alguna pieza eliminable directamente (CON PRIORIDADES). Puede devolver nullptr
std::pair<PieceSprite*, Vec2> confirmKill(VcPieces pieces);

// Obtener mejor objetivo de ataque (pieza atacante + posición a atacar)
std::pair<PieceSprite*, Vec2> getAttackObjective(VcPieces pieces);

// Obtener mejor casilla de movimiento (pieza atacante + posición a moverse)
std::pair<PieceSprite*, Vec2> getMoveObjective(VcPieces pieces);

// Devuelve la casilla más cercana al nexo desde las casillas parámetro
Vec2 getNexusPos(std::vector<Vec2> availablePositions);

void aiMovePiece(VcPieces& pieces, Game *game)
{

}
