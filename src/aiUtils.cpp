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
Vec2 getNexusRoute(vector<Vec2> availablePositions);

void aiMovePiece(VcPieces& pieces, Game *game)
{
    pair<PieceSprite*, Vec2> move = confirmKill(pieces,game);
    if (move.first != nullptr) {
        int result = updatePiece(game, move.first->getY()/64 - 1, move.first->getX()/64 - 6, (int) move.second.x, (int) move.second.y);
        PieceSprite *piece = &pieces[move.first->id - 1];
        if (result == 3) {
            if (piece->id >= 17 && piece->id <= 19) { // Mago no se mueve al matar
                piece->setAttackDir(Vec2(piece->getX()/64 - 6, piece->getY()/64 - 1), Vec2(move.second.x, move.second.y));
                piece->attack_timer = Time::seconds + 0.2;
                piece->positionBuffer.x = piece->getX();
                piece->positionBuffer.y = piece->getY();
                piece->state = PieceSprite::ATTACKING;
            } else {
                piece->focus = Vec2((int) ((move.second.y + 6.5) * 64), (move.second.x + 1) * 64);
                piece->state = PieceSprite::MOVING;
            }
        } else {
            cout << "Error: el ataque debería haber destruído la pieza." << endl; // TODO?
        }
    }
    else {
        move = getAttackObjective(pieces, game);
        if (move.first != nullptr){     // Ataque normal
            int result = updatePiece(game, move.first->getY()/64 - 1, move.first->getX()/64 - 6, (int) move.second.x, (int) move.second.y);
            PieceSprite *piece = &pieces[move.first->id - 1];
            if (result == 2) {
                piece->setAttackDir(Vec2(piece->getX()/64 - 6, piece->getY()/64 - 1), Vec2(move.second.x, move.second.y));
                piece->attack_timer = Time::seconds + 0.2;
                piece->positionBuffer.x = piece->getX();
                piece->positionBuffer.y = piece->getY();
                piece->state = PieceSprite::ATTACKING;
            } else {
                cout << "Error de ataque." << endl; // TODO?
            }
        } else {                        // Movimiento
            move = getMoveObjective(pieces,game);
            if (move.first != nullptr) {
                if (updatePiece(game, move.first->getY() / 64 - 1, move.first->getX() / 64 - 6, (int) move.second.x, (int) move.second.y) == 1) {
                    PieceSprite::selectedPiece = move.first->id;
                    pieces[move.first->id - 1].state = PieceSprite::MOVING;
                    pieces[move.first->id - 1].focus = Vec2((int) ((move.second.y + 6.5) * 64), (move.second.x + 1) * 64);
                } else {
                    move.first->state = PieceSprite::IDLE;
                    PieceSprite::selectedPiece = 0;
                }
            } else {
                cout << "ERROR" << endl;
            }
        }
    }
}

vector<Vec2> positionsToCoords(const vector<Vec2>& positions)
{
    vector<Vec2> coordinates;
    coordinates.reserve(positions.size()); // Reservar para optimizar
    for (auto & position:positions) {
        coordinates.emplace_back((int) position.y/64 - 1, (int) position.x/64 - 6);
    }
    return coordinates;
}

map<PieceSprite*, vector<Vec2>> getAvailableSquares(VcPieces pieces, Game *game, bool attack)
{
    map<PieceSprite*, vector<Vec2>> squares;
    if (!attack) {
        for (int i = 12; i < pieces.size(); ++i) {
            squares[&pieces[i]] = positionsToCoords(pieces[i].getMovePositions(game->data));
        }
    } else {
        for (int i = 12; i < pieces.size(); ++i) {
            squares[&pieces[i]] = positionsToCoords(pieces[i].getAttackPositions(game->data));
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
            if (pieces[pieceID - 1].hp <= getBaseDmg(square.first->id)) {                             // Si la pieza es eliminable,
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
            if (position.y >= 9) {  // Si la pieza se acerca al nexo
                threatOptions.emplace_back(square.first, Vec2(position.x, position.y));  // Añadirla a las amenazas
            } else if (pieces[pieceID].hp < getBaseHp(pieceID)* 0.6 ||      // Pieza tocada
                (pieceID >= 8 && pieceID <= 10) ||                          // Pieza enemioga es un mago
                (square.first->id >= 20 && square.first->id <= 22) ||       // Mi pieza es un mago
                rand() % 4 == 2                                             // Ataque aletorio
            ) {
                focusOptions.emplace_back(square.first, Vec2(position.x, position.y));
            }
        }
    }

    if (!threatOptions.empty()){    // Si hay piezas que supongan una amenaza
        pair<PieceSprite*, Vec2> focus = threatOptions[0];
        for (auto & option:threatOptions) { // Iterar sobre las opciones para elegir la mejor opción
            if (hasHigherKillPriority(option.first->id, focus.first->id)) { // Elegir prioridad
                focus = option;
            }
        }
        return focus;
    } else if (!focusOptions.empty()) {     // Si hay piezas que deberían ser atacadas
        int randomInt = rand() % focusOptions.size();   // Opción aleatoria
        return focusOptions[randomInt];
    } else {
        return make_pair(nullptr, Vec2()); // Si no hay casillas eliminables devolver nullptr
    }
}

pair<PieceSprite*, Vec2> getMoveObjective(VcPieces pieces, Game *game)
{
    vector<pair<PieceSprite*, Vec2>> movementOptions; // Posibles opciones para moverse
    map<PieceSprite*, vector<Vec2>> moveSquares = getAvailableSquares(pieces, game, false);
    for (auto & square:moveSquares) { // Iterar todos los pares Pieza-casillas
        if (!square.second.empty()){
            Vec2 casilla = getNexusRoute(square.second);
            if (abs(casilla.x + casilla.y - pieces[25].getX() - pieces[25].getY()) < 5){
                movementOptions.emplace_back(square.first, Vec2(casilla.x, casilla.y));   // añadirla a las opciones
            }
        }
    }
    if (!movementOptions.empty()){
        pair<PieceSprite*, Vec2> focus = movementOptions[0];
        for (auto & option:movementOptions) { // Iterar sobre las opciones para elegir la mejor opción
            if (abs(option.second.x + option.second.y -pieces[25].getX() -pieces[25].getY()) <
            abs(focus.second.x + focus.second.y -pieces[25].getX() -pieces[25].getY())) { // Elegir prioridad
                focus = option;
            }
        }
        return focus;
    } else {
        for (auto & square:moveSquares) { // Iterar todos los pares Pieza-casillas
            if (!square.second.empty()){
                Vec2 casilla= getNexusRoute(square.second);
                movementOptions.emplace_back(square.first, Vec2(casilla.x, casilla.y));   // añadirla a las opciones
            }
        }
        int randomInt = rand() % movementOptions.size();
        return movementOptions[randomInt];
    }
}

double distanceToNexus(Vec2 position)
{
    return sqrt(pow(position.x - 3, 2) + pow(position.y, 2));
}

Vec2 getNexusRoute(vector<Vec2> availablePositions)
{
    double distance = distanceToNexus(availablePositions[0]);
    int index = 0;
    for (int i = 1; i < availablePositions.size(); i++) {
        double currentDistance = distanceToNexus(availablePositions[i]);
        if (currentDistance < distance) {
            distance = currentDistance;
            index = i;
        }
    }
    return availablePositions[index];
}