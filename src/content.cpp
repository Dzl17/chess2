#include "content.h"

String getSpritePath(int id);
int getIconIndex(int id);
void loadPieces(Game *gameRef, vector<PieceSprite> *pieces);
char * getPieceName(int id);
void writePieceHp(Batch *batch, PieceSprite& piece);
void writePieceDmg(Batch *batch, PieceSprite& piece);

SpriteFont font;

void Assets::load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Game *game, int *mode)
{
    startGame(game, 1,1);

    statics->clear();
    buttons->clear();
    pieces->clear();
    nexuses->clear();

    font = SpriteFont("../data/fonts/dogica.ttf", 32);

    buttons->push_back(GuiButton(512, 1128, 256, 108, // Play (menu)
                                 "../data/img/buttons/playMenuButtonIdle.png", "../data/img/buttons/playMenuButtonPressed.png"));
    buttons->push_back(GuiButton(512, 1544, 256, 108, // Forms (menu)
                                 "../data/img/buttons/formsMenuButtonIdle.png", "../data/img/buttons/formsMenuButtonPressed.png"));
    buttons->push_back(GuiButton(512, 1960, 256, 108, // Exit (menu)
                                 "../data/img/buttons/exitMenuButtonIdle.png", "../data/img/buttons/exitMenuButtonPressed.png"));
    buttons->push_back(GuiButton(16, 16, 224, 64, // Help (game)
                                 "../data/img/buttons/helpButtonIdle.png", "../data/img/buttons/helpButtonPressed.png"));
    buttons->push_back(GuiButton(16, 96, 224, 64, // Exit (game)
                                 "../data/img/buttons/exitButtonIdle.png", "../data/img/buttons/exitButtonPressed.png"));

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

    statics->push_back(StaticSprite(0, 0, "../data/img/mainMenu.png", true)); // Fondo (menu)

    loadPieces(game, pieces);

    nexuses->push_back(NexusSprite(416, 256, "../data/img/nexusL.png"));
    nexuses->push_back(NexusSprite(1056, 256, "../data/img/nexusR.png"));
}

void Assets::render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Batch *batch, Game game, int *mode)
{
    if (*mode == 0) (*statics)[10].draw(batch); // Fondo
    if (*mode == 1) (*statics)[0].draw(batch); // Fondo
    if (*mode == 2) (*statics)[0].draw(batch); // Fondo

    if (*mode == 0) {
        for (int i = 0; i <= 2; i++) {
            (*buttons)[i].draw(batch);
        }
    } else if (*mode == 1) {
        for (int i = 3; i <= 4; i++) {
            (*buttons)[i].draw(batch);
        }

        if (game.turn % 2 == 0) batch->rect(Rect(416, 256, 64, 64), Color("#8a0da6"));
        else batch->rect(Rect(1056, 256, 64, 64), Color("#8a0da6"));

        for (auto & piece : *pieces) {
            if (piece.state == PieceSprite::CHOOSING && piece.active) {
                batch->rect_line(Rect((float)piece.getX(), (float)piece.getY(), 64, 64), 2, Color::black);

                (*statics)[getIconIndex(piece.id)].draw(batch); // Iconos de unidades seleccionadas

                for (auto & pos : piece.getMovePositions(game.data)) { // Rectángulos de posiciones de movimiento
                    batch->rect_rounded(Rect(pos.x + 16, pos.y + 16, 32, 32), 32,10, Color("1ebc73"));
                }
                for (auto & pos : piece.getAttackPositions(game.data)) { // Rectángulos de posiciones de ataque
                    batch->rect(Rect(pos.x + 4, pos.y + 4, 56, 56), Color("#e83b3b"));
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
    } else if (*mode == 2) {

    }
}

void Assets::update(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Batch *batch, Game *game, int *mode)
{
    for (auto & piece : *pieces) piece.update();

    for (auto & nexus : *nexuses) nexus.update();

    for (auto & button : *buttons) button.update();

    if (*mode == 0) {
        if ((*buttons)[0].isClicked() || Input::pressed(Key::P)) *mode = 1; // Play
        if ((*buttons)[1].isClicked() || Input::pressed(Key::F)) std::cout << "FORMACIONES" << std::endl; // Forms TODO
        if ((*buttons)[2].isClicked() || Input::pressed(Key::Escape)) App::exit(); // Exit

        (*buttons)[0].setY((int) ((*buttons)[0].getY() + (328 - (*buttons)[0].getY()) * (double) Time::delta * 4)); // Movimiento de los botones de inicio
        (*buttons)[1].setY((int) ((*buttons)[1].getY() + (444 - (*buttons)[1].getY()) * (double) Time::delta * 4));
        (*buttons)[2].setY((int) ((*buttons)[2].getY() + (560 - (*buttons)[2].getY()) * (double) Time::delta * 4));
    } else if (*mode == 1) {
        if ((*buttons)[3].isClicked() || Input::pressed(Key::H)) (*statics)[1].swapActive();
        if ((*buttons)[4].isClicked() || Input::pressed(Key::Escape)) {
            *mode = 0;
            Assets::load(statics, buttons, pieces, nexuses, game, mode);
        }
    } else if (*mode == 2) {

    }
}

void loadPieces(Game *gameRef, vector<PieceSprite> *pieces)
{
    for (int i = 0; i < B_ROWS; i++) {
        for (int j = 0; j < B_COLUMNS; j++) {
            int dataCode = gameRef->data[i][j];
            if (dataCode >= 1 && dataCode <= 24) pieces->push_back(PieceSprite(
                    j * 64 + 416,
                    i * 64 + 64,
                    dataCode,
                    getSpritePath(dataCode),
                    gameRef));
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

void Login::runSetup()
{

}