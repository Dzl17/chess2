#include "aiUtils.h"
#include <map>
#include <cmath>

using namespace std;

// Pasar posicion introducida a coordenadas de tablero
vector<Vec2> positionsToCoords(const vector<Vec2>& positions);

// Posiciones disponibles, el flag de 'attack' coge las de ataque en vez de las de defensa
map<PieceSprite*, vector<Vec2>> getAvailableSquares(VcPieces pieces, Game *game, bool attack);

// Evaluar si hay alguna pieza eliminable directamente (CON PRIORIDADES). Puede devolver nullptr
pair<PieceSprite*, Vec2> confirmKill(VcPieces pieces, Game *game);

// Deuvelve si la id 'comparingID' tiene mayor prioridad de eliminación que la id 'baseID'
// Orden: Asesino-Mago-Golem-Lancero
bool hasHigherKillPriority(int comparingID, int baseID);

// Obtener mejor objetivo de ataque (pieza atacante + posición a atacar)
pair<PieceSprite*, Vec2> getAttackObjective(VcPieces pieces, Game *game);

// Obtener mejor casilla de movimiento (pieza atacante + posición a moverse)
pair<PieceSprite*, Vec2> getMoveObjective(VcPieces pieces, Game *game);

// Devuelve la casilla más cercana al nexo desde las casillas parámetro
Vec2 getNexusPos(vector<Vec2> availablePositions, Game *game);

void aiMovePiece(VcPieces& pieces, Game *game)
{
    getAvailableSquares(pieces,game,true);
}

vector<Vec2> positionsToCoords(const vector<Vec2>& positions)
{
    vector<Vec2> coordinates;
    coordinates.reserve(positions.size()); // Reservar para optimizar
    for (auto & position:positions) {
        coordinates.emplace_back(position.y/64 - 1, position.x/64 - 6);
    }
    return coordinates;
}

map<PieceSprite*, vector<Vec2>> getAvailableSquares(VcPieces pieces, Game *game, bool attack)
{
    map<PieceSprite*, vector<Vec2>> squares;
    if (!attack) {
        for (auto & piece:pieces) {
            squares[&piece] = positionsToCoords(piece.getMovePositions(game->data));
        }
    } else {
        for (auto & piece:pieces) {
            squares[&piece] = positionsToCoords(piece.getAttackPositions(game->data));
        }
    }
    return squares;
}

pair<PieceSprite*, Vec2> confirmKill(VcPieces pieces, Game *game)
{
    vector<pair<PieceSprite*, Vec2>> focusOptions; // Posibles opciones para atacar
    map<PieceSprite*, vector<Vec2>> attackSquares = getAvailableSquares(pieces, game, true);
    for (auto & square:attackSquares) { // Iterar todos los pares Pieza-casillas
        for (auto & position:square.second) { // Iterar todas las casillas atacables
            int pieceID = game->data[(int) position.x][(int) position.y]; // ID de la pieza atacable
            if (pieces[pieceID].hp <= square.first->getDmg()) {                             // Si la pieza es eliminable,
                focusOptions.emplace_back(square.first, Vec2(position.x, position.y));   // añadirla a las opciones
            }
        }
    }
    if (focusOptions.empty()) return make_pair(nullptr, Vec2()); // Si no hay casillas eliminables devolver nullptr
    pair<PieceSprite*, Vec2> focus = focusOptions[0];
    for (auto & option:focusOptions) { // Iterar sobre las opciones para elegir la mejor opción
        if (hasHigherKillPriority(option.first->id, focus.first->id)) { // Elegir prioridad
            focus = option;
        }
    }
    return focus;
}

bool hasHigherKillPriority(int comparingID, int baseID)
{
    int comparingPriority, basePriority;

    if (comparingID <= 4) comparingPriority = 1;
    else if (comparingID <= 7) comparingPriority = 3;
    else if (comparingID <= 10) comparingPriority = 4;
    else comparingPriority = 2;

    if (baseID <= 4) basePriority = 1;
    else if (baseID <= 7) basePriority = 3;
    else if (baseID <= 10) basePriority = 4;
    else basePriority = 2;

    return comparingPriority > basePriority;
}

pair<PieceSprite*, Vec2> getAttackObjective(VcPieces pieces, Game *game)
{
    vector<pair<PieceSprite*, Vec2>> threatOptions; // Posibles opciones para atacar
    vector<pair<PieceSprite*, Vec2>> focusOptions; // Posibles opciones para atacar
    map<PieceSprite*, vector<Vec2>> attackSquares = getAvailableSquares(pieces, game, true);

    for (auto & square:attackSquares) { // Iterar todos los pares Pieza-casillas
        for (auto & position:square.second) { // Iterar todas las casillas atacables
            int pieceID = game->data[(int) position.x][(int) position.y]; // ID de la pieza atacable
            if (position.y >= 9) {  //Si la pieza se acerca al nexo
                threatOptions.emplace_back(square.first, Vec2(position.x, position.y));   // añadirla a las opciones
            } else if (pieces[pieceID].hp < getBaseHp(pieceID)* 0.6 || //Pieza tocada
                (pieceID >= 8 && pieceID <= 10) || //Pieza enemioga es un mago
                (square.first->id >= 20 && square.first->id <= 22) ||       //Mi pieza es un mago
                rand() % 4 == 2
                ) {  //Ataque aletorio
                focusOptions.emplace_back(square.first, Vec2(position.x, position.y));
            }
        }
    }

    if (!threatOptions.empty()){
        pair<PieceSprite*, Vec2> focus = threatOptions[0];
        for (auto & option:threatOptions) { // Iterar sobre las opciones para elegir la mejor opción
            if (hasHigherKillPriority(option.first->id, focus.first->id)) { // Elegir prioridad
                focus = option;
            }
        }
        return focus;
    } else if (!focusOptions.empty()) {
        int randomInt = rand() % focusOptions.size();
        return focusOptions[randomInt];
    } else {
        return make_pair(nullptr, Vec2()); // Si no hay casillas eliminables devolver nullptr
    }

}

pair<PieceSprite*, Vec2> getMoveObjective(VcPieces pieces, Game *game)
{

}

Vec2 getNexusPos(vector<Vec2> availablePositions, Game *game)
{

}