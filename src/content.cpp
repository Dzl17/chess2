#include "content.h"
extern "C" {
    #include "game/piece.h"
}

#define MOVE true
#define ATTACK false

vector<Vec2> getMovePositions(int id, int x, int y, int data[B_ROWS][B_COLUMNS]);
vector<Vec2> getAttackPositions(int id, int x, int y, int data[B_ROWS][B_COLUMNS]);

void Assets::load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces)
{
    statics->push_back(StaticSprite(0, 0, "../data/img/background.png", true));
    statics->push_back(StaticSprite(320, 64, "../data/img/helpmenu.png", false));

    buttons->push_back(GuiButton(16, 16, 224, 64,
                                 "../data/img/helpButtonIdle.png", "../data/img/helpButtonPressed.png"));
    buttons->push_back(GuiButton(16, 96, 224, 64,
                                 "../data/img/exitButtonIdle.png", "../data/img/exitButtonPressed.png"));

    pieces->push_back(PieceSprite(416, 192, 1, "../data/img/units/spearmanL.png"));
    pieces->push_back(PieceSprite(480, 128, 5, "../data/img/units/wizardL.png"));
    pieces->push_back(PieceSprite(416, 128, 8, "../data/img/units/assassinL.png"));
    pieces->push_back(PieceSprite(416, 256, 11, "../data/img/units/golemL.png"));

    pieces->push_back(PieceSprite(992, 192, 13, "../data/img/units/spearmanR.png"));
    pieces->push_back(PieceSprite(1056, 128, 17, "../data/img/units/wizardR.png"));
    pieces->push_back(PieceSprite(992, 128, 20, "../data/img/units/assassinR.png"));
    pieces->push_back(PieceSprite(1056, 192 ,23, "../data/img/units/golemR.png"));
}

void Assets::render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, Batch *batch, Game game)
{
    (*statics)[0].draw(batch); // Fondo

    for (auto & button : *buttons) {
        button.draw(batch);
    }

    for (auto & piece : *pieces) {
        piece.update();
        if (piece.state == PieceSprite::CHOOSING) {
            for (auto & pos : getMovePositions(piece.id, piece.getX(), piece.getY(), game.data)) {
                if (MOVE) batch->rect(Rect(pos.x, pos.y, 64, 64), Color::green);
            }
            for (auto & pos : getAttackPositions(piece.id, piece.getX(), piece.getY(), game.data)) {
                if (ATTACK) batch->rect(Rect(pos.x, pos.y, 64, 64), Color::red);
            }
        }

    }
    for (auto & piece : *pieces) {
        piece.draw(batch);
    }

    (*statics)[1].draw(batch);
}

void Assets::updateGame(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, Game *game)
{

    for (auto & piece : *pieces) {
        piece.update();
    }

    for (auto & button : *buttons) {
        button.update();
    }
}

void Assets::updateMenu(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces)
{

}


vector<Vec2> getMovePositions(int id, int x, int y, int data[B_ROWS][B_COLUMNS])
{
    int relX = x/64 - 6;
    int relY = y/64 - 1;
    vector<Vec2> positions;
    switch (pieceCode(id)) {
        case 0: // Lancero
            if (id <= 12) {
                if (relX + 1 <= 10) positions.emplace_back(Vec2(x + 64, y));
                if (relX + 2 <= 10) positions.emplace_back(Vec2(x + 128, y));
            } else {
                if (relX - 1 >= 0)  positions.emplace_back(Vec2(x - 64, y));
                if (relX - 2 >= 0)  positions.emplace_back(Vec2(x - 128, y));
            }
            break;
        case 2: // Asesino
            for (int i = -3; i <= 3; i++) {
                if (i == 0) continue;
                if (relX + i <= 10 && relX + i >= 0) positions.emplace_back(Vec2(x + i*64, y));
                if (relY + i <= 6  && relY + i >= 0) positions.emplace_back(Vec2(x, y + i*64));
            }
            break;
        case 1: // Mago
        case 3: // Golem
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue;
                    else if (relX + i <= 10 && relX + i >= 0 && relY + j <= 6 && relY + j >= 0)
                        positions.emplace_back(x + i*64, y + j*64);
                }
            }
            break;
    }
    for (auto it = positions.begin(); it != positions.end();) {
        if (data[(int) (it->y/64 - 1)][(int) (it->x/64 - 6)] == 0) it++;
        else positions.erase(it);
    }
    return positions;
}

vector<Vec2> getAttackPositions(int id, int x, int y, int data[B_ROWS][B_COLUMNS])
{
    int relX = x/64 - 6;
    int relY = y/64 - 1;
    vector<Vec2> positions;
    switch (pieceCode(id)) {
        case 0: // Lancero
            if (id <= 12) {
                if (relX + 1 <= 10) {
                    if (relY     <= 6 && relY     >= 0) positions.emplace_back(Vec2(x + 64, y));
                    if (relY + 1 <= 6 && relY + 1 >= 0) positions.emplace_back(Vec2(x + 64, y + 64));
                    if (relY - 1 <= 6 && relY - 1 >= 0) positions.emplace_back(Vec2(x + 64, y - 64));
                }
            } else {
                if (relX - 1 >= 0) {
                    if (relY     <= 6 && relY     >= 0) positions.emplace_back(Vec2(x - 64, y));
                    if (relY + 1 <= 6 && relY + 1 >= 0) positions.emplace_back(Vec2(x - 64, y + 64));
                    if (relY - 1 <= 6 && relY - 1 >= 0) positions.emplace_back(Vec2(x - 64, y - 64));
                }
            }
            break;
        case 2: // Asesino
            if (relX + 1 <= 10)  positions.emplace_back(Vec2(x + 64, y));
            if (relX - 1 >= 0)  positions.emplace_back(Vec2(x - 64, y));
            if (relY + 1 <= 6) positions.emplace_back(Vec2(x, y + 64));
            if (relY - 1 >= 0)  positions.emplace_back(Vec2(x, y - 64));
            break;
        case 1: // Mago
            // Arriba y abajo
            for (int i = -2; i <= 2; i++) {
                if (relX + i <= 10 && relX + i >= 0) {
                    if (relY + 2 <= 6) positions.emplace_back(Vec2(x + i*64, y + 128));
                    if (relY - 2 >= 0) positions.emplace_back(Vec2(x + i*64, y - 128));
                }
            }
            // Lados
            for (int i = -1; i <= 1; i++) {
                if (relY + i <= 6 && relY + i >= 0) {
                    if (relX + 2 <= 10) positions.emplace_back(Vec2(x + 128, y + i*64));
                    if (relX - 2 >= 0) positions.emplace_back(Vec2(x - 128, y + i*64));
                }
            }
            break;
        case 3: // Golem
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue;
                    else if (relX + i <= 10 && relX + i >= 0 && relY + j <= 6 && relY + j >= 0) positions.emplace_back(x + i*64, y + j*64);
                }
            }
            break;
    }
    for (auto it = positions.begin(); it != positions.end();) {
        int team = id <= 12 ? 0 : 1;
        int posCode = data[(int) (it->y/64 - 1)][(int) (it->x/64 - 6)];
        if (team == 0) {
            if (posCode >= 13 && posCode != 25) positions.erase(it);
            else it++;
        } else if (team == 1) {
            if (posCode <= 12 || posCode == 26) positions.erase(it);
            else it++;
        }
    }
    return positions;
}