#include "content.h"

String getSpritePath(int id);
int getIconIndex(int id);
void loadPieces(vector<PieceSprite> *pieces, int data[B_ROWS][B_COLUMNS]);
char * getPieceName(int id);
void writePieceHp(Batch *batch, PieceSprite& piece);
void writePieceDmg(Batch *batch, PieceSprite& piece);

SpriteFont font;

void Assets::load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Game game)
{
    font = SpriteFont("../data/fonts/dogica.ttf", 32);

    statics->push_back(StaticSprite(0, 0, "../data/img/background.png", true));
    statics->push_back(StaticSprite(320, 64, "../data/img/helpmenu.png", false));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/spearmanLIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/spearmanRIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/wizardLIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/wizardRIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/assassinLIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/assassinRIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/golemLIcon.png", true));
    statics->push_back(StaticSprite(480, 556, "../data/img/icons/golemRIcon.png", true));

    buttons->push_back(GuiButton(16, 16, 224, 64,
                                 "../data/img/helpButtonIdle.png", "../data/img/helpButtonPressed.png"));
    buttons->push_back(GuiButton(16, 96, 224, 64,
                                 "../data/img/exitButtonIdle.png", "../data/img/exitButtonPressed.png"));

    loadPieces(pieces, game.data);

    nexuses->push_back(NexusSprite(416, 256, "../data/img/nexusL.png"));
    nexuses->push_back(NexusSprite(1056, 256, "../data/img/nexusR.png"));
}

void Assets::render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Batch *batch, Game game)
{
    (*statics)[0].draw(batch); // Fondo

    for (auto & button : *buttons) {
        button.draw(batch);
    }

    for (auto & piece : *pieces) {
        if (piece.state == PieceSprite::CHOOSING) {
            batch->rect_line(Rect((float)piece.getX(), (float)piece.getY(), 64, 64), 2, Color::black);

            (*statics)[getIconIndex(piece.id)].draw(batch); // Iconos de unidades seleccionadas

            for (auto & pos : piece.getMovePositions(game.data)) { // Rectángulos de posiciones de movimiento
                batch->rect_rounded(Rect(pos.x + 16, pos.y + 16, 32, 32), 32,10, Color::green);
            }
            for (auto & pos : piece.getAttackPositions(game.data)) { // Rectángulos de posiciones de ataque
                batch->rect(Rect(pos.x + 4, pos.y + 4, 56, 56), Color::red);
            }

            batch->str(font, getPieceName(piece.getPieceCode()), Vec2(620, 568), Color("#1ebc73"));
            writePieceHp(batch, piece);
            writePieceDmg(batch, piece);
        }
    }
    for (auto & piece : *pieces) {
        piece.draw(batch);
    }

    for (auto & nexus : *nexuses) {
        nexus.draw(batch);
    }

    (*statics)[1].draw(batch);
}

void Assets::updateGame(vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Game *game)
{
    for (auto & piece : *pieces) {
        piece.update(game);
    }

    for (auto & nexus : *nexuses) {
        nexus.update();
    }

    for (auto & button : *buttons) {
        button.update();
    }
}

void Assets::updateMenu(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces)
{

}

void loadPieces(vector<PieceSprite> *pieces, int data[B_ROWS][B_COLUMNS])
{
    for (int i = 0; i < B_ROWS; i++) {
        for (int j = 0; j < B_COLUMNS; j++) {
            int dataCode = data[i][j];
            if (dataCode >= 1 && dataCode <= 24) pieces->push_back(PieceSprite(
                    (j + 6.5) * 64, // Wtf
                    (i + 1) * 64,
                    dataCode,
                    getSpritePath(dataCode)));
        }
    }

}

String getSpritePath(int id)
{
    if (id >= 1 && id <= 4) {
        return "../data/img/units/spearmanL.png";
    } else if (id >= 5 && id <= 7) {
        return "../data/img/units/wizardL.png";
    } else if (id >= 8 && id <= 10) {
        return "../data/img/units/assassinL.png";
    } else if (id >= 11 && id <= 12) {
        return "../data/img/units/golemL.png";
    } else if (id >= 13 && id <= 16) {
        return "../data/img/units/spearmanR.png";
    } else if (id >= 17 && id <= 19) {
        return "../data/img/units/wizardR.png";
    } else if (id >= 20 && id <= 22) {
        return "../data/img/units/assassinR.png";
    } else if (id >= 23 && id <= 24) {
        return "../data/img/units/golemR.png";
    } else if (id == 25) {
        return "../data/img/boredlion.png";
    } else if (id == 26) {
        return "../data/img/boredlion.png";
    } else {
        return "../data/img/boredlion.png";
    }
}

int getIconIndex(int id)
{
    if (id >= 1 && id <= 4) {
        return 2;
    } else if (id >= 5 && id <= 7) {
        return 4;
    } else if (id >= 8 && id <= 10) {
        return 6;
    } else if (id >= 11 && id <= 12) {
        return 8;
    } else if (id >= 13 && id <= 16) {
        return 3;
    } else if (id >= 17 && id <= 19) {
        return 5;
    } else if (id >= 20 && id <= 22) {
        return 7;
    } else if (id >= 23 && id <= 24) {
        return 9;
    } else {
        return 0;
    }
}

char * getPieceName(int id) {
    switch (id) {
        case 0:
            return (char*) "Spearman";
        case 1:
            return (char*) "Wizard";
        case 2:
            return (char*) "Assassin";
        case 3:
            return (char*) "Golem";
        default:
            return (char*) "";
    }
}

void writePieceHp(Batch *batch, PieceSprite& piece)
{
    // Dibujar HP
    char hp_int_str[4]; // n+1 de tamaño mínimo, siendo n los dígitos del int
    sprintf(hp_int_str, "%d", piece.hp);
    char hp_str[64] = "HP:";
    strcat(hp_str, hp_int_str);
    batch->str(font, hp_str, Vec2(620, 604), Color::black);
}

void writePieceDmg(Batch *batch, PieceSprite& piece)
{
    // Dibujar DMG
    char dmg_int_str[4]; // n+1 de tamaño mínimo, siendo n los dígitos del int
    sprintf(dmg_int_str, "%d", piece.getDmg());
    char dmg_str[64] = "DMG:";
    strcat(dmg_str, dmg_int_str);
    batch->str(font, dmg_str, Vec2(620, 640), Color::black);
}