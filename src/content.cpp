#include "content.h"

String getSpritePath(int id);
std::string getIconKey(int id);
void loadPieceCoords(Game *gameRef, VcPieces *pieces);
char * getPieceName(int id);
void renderFormation(Batch *batch, VcPieces *pieces, const char *formation, TextureRef blueNexusTex);
TextureRef getPieceTexture(VcPieces *pieces, char pieceLetter);
void writeFormSetPos(Batch *batch, FormationSet *formSet);
void writePieceHp(Batch *batch, PieceSprite& piece);
void writePieceDmg(Batch *batch, PieceSprite& piece);

SpriteFont font;

void Assets::load(UmStatics *statics, UmButtons *buttons, VcPieces *pieces, VcNexuses *nexuses, Game *game, int *mode, FormationSet *formSet)
{
    statics->clear();
    buttons->clear();
    pieces->clear();
    nexuses->clear();

    font = SpriteFont("../data/fonts/dogica.ttf", 32);

    buttons->insert({"playMenuButton", new GuiButton(512, 1128, 256, 108, // Play (menu)
                                 "../data/img/buttons/playMenuButtonIdle.png", "../data/img/buttons/playMenuButtonPressed.png")});
    buttons->insert({"formsMenuButton", new GuiButton(512, 1544, 256, 108, // Forms (menu)
                                 "../data/img/buttons/formsMenuButtonIdle.png", "../data/img/buttons/formsMenuButtonPressed.png")});
    buttons->insert({"exitMenuButton", new GuiButton(512, 1960, 256, 108, // Exit (menu)
                                 "../data/img/buttons/exitMenuButtonIdle.png", "../data/img/buttons/exitMenuButtonPressed.png")});

    buttons->insert({"leftArrowButton", new GuiButton(352, 264, 128, 128,
                                                      "../data/img/buttons/leftArrowIdle.png", "../data/img/buttons/leftArrowPressed.png")});
    buttons->insert({"rightArrowButton", new GuiButton(800, 264, 128, 128,
                                                     "../data/img/buttons/rightArrowIdle.png", "../data/img/buttons/rightArrowPressed.png")});
    buttons->insert({"startButton", new GuiButton(512, 586, 256, 108,
                                                     "../data/img/buttons/startButtonIdle.png", "../data/img/buttons/startButtonPressed.png")});

    buttons->insert({"helpGameButton", new GuiButton(16, 16, 224, 80, // Help (game)
                                 "../data/img/buttons/helpButtonIdle.png", "../data/img/buttons/helpButtonPressed.png")});
    buttons->insert({"menuGameButton", new GuiButton(16, 112, 224, 80, // Menu (game)
                                 "../data/img/buttons/menuButtonIdle.png", "../data/img/buttons/menuButtonPressed.png")});
    buttons->insert({"exitGameButton", new GuiButton(16, 208, 224, 80, // Exit (game)
                                 "../data/img/buttons/exitButtonIdle.png", "../data/img/buttons/exitButtonPressed.png")});

    statics->insert({"backgroundG",   new StaticSprite(0,     0, "../data/img/backgroundG.png",         true)});
    statics->insert({"backgroundB",   new StaticSprite(0,     0, "../data/img/backgroundB.png",         true)});
    statics->insert({"helpMenu",      new StaticSprite(320,  64, "../data/img/helpmenu.png",            false)});
    statics->insert({"spearmanLIcon", new StaticSprite(480, 556, "../data/img/icons/spearmanLIcon.png", true)});
    statics->insert({"spearmanRIcon", new StaticSprite(480, 556, "../data/img/icons/spearmanRIcon.png", true)});
    statics->insert({"wizardLIcon",   new StaticSprite(480, 556, "../data/img/icons/wizardLIcon.png",   true)});
    statics->insert({"wizardRIcon",   new StaticSprite(480, 556, "../data/img/icons/wizardRIcon.png",   true)});
    statics->insert({"assassinLIcon", new StaticSprite(480, 556, "../data/img/icons/assassinLIcon.png", true)});
    statics->insert({"assassinRIcon", new StaticSprite(480, 556, "../data/img/icons/assassinRIcon.png", true)});
    statics->insert({"golemLIcon",    new StaticSprite(480, 556, "../data/img/icons/golemLIcon.png",    true)});
    statics->insert({"golemRIcon",    new StaticSprite(480, 556, "../data/img/icons/golemRIcon.png",    true)});
    statics->insert({"mainMenu",      new StaticSprite(0,     0, "../data/img/mainMenu.png",            true)});
    statics->insert({"leftSideTable", new StaticSprite(536, 96, "../data/img/leftSideTable.png",       true)});

    for (int i = 1; i <= 24; i++) {
        pieces->push_back(PieceSprite(0,0, i,getSpritePath(i), game));
    }

    nexuses->push_back(NexusSprite( 416, 256, "../data/img/nexusL.png"));
    nexuses->push_back(NexusSprite(1056, 256, "../data/img/nexusR.png"));
}

void Assets::render(UmStatics statics, UmButtons buttons, VcPieces *pieces, VcNexuses *nexuses, Game game, int *mode, FormationSet *formSet, Batch *batch)
{
    if (*mode == 0) { // Menú principal
        statics["mainMenu"]->draw(batch); // Fondo
        buttons["playMenuButton"]->draw(batch);
        buttons["formsMenuButton"]->draw(batch);
        buttons["exitMenuButton"]->draw(batch);
    } else if (*mode == 1) { // Selección de formación
        buttons["leftArrowButton"]->draw(batch);
        buttons["rightArrowButton"]->draw(batch);
        buttons["startButton"]->draw(batch);
        statics["leftSideTable"]->draw(batch);
        renderFormation(batch, pieces, formSet->forms[formSet->index], (*nexuses)[0].texture);
        writeFormSetPos(batch, formSet);
    } else if (*mode == 2) {
        statics["backgroundG"]->draw(batch); // Fondo
        buttons["helpGameButton"]->draw(batch);
        buttons["menuGameButton"]->draw(batch);
        buttons["exitGameButton"]->draw(batch);

        // Vida de los nexos
        batch->rect(Rect(404, 700, 8, (float)game.nexus1hp * (-112) / NEXUS_HP), Color("4d9be6")); // Vida azul
        batch->rect(Rect(1124, 700, 8, (float)game.nexus2hp * (-112) / NEXUS_HP), Color("ea4f36")); // Vida roja

        if (game.turn % 2 == 0) batch->rect(Rect(416, 256, 64, 64), Color("#8a0da6"));
        else batch->rect(Rect(1056, 256, 64, 64), Color("#8a0da6"));

        for (auto & piece : *pieces) {
            if (piece.state == PieceSprite::CHOOSING && piece.active) {
                batch->rect_line(Rect((float)piece.getX(), (float)piece.getY(), 64, 64), 2, Color::black); // Pieza seleccionada

                statics[getIconKey(piece.id)]->draw(batch); // Iconos de unidades seleccionadas

                for (auto & pos : piece.getMovePositions(game.data)) { // Rectángulos de posiciones de movimiento
                    batch->rect_rounded(Rect(pos.x + 16, pos.y + 16, 32, 32), 32,10, Color("1ebc73"));
                }
                for (auto & pos : piece.getAttackPositions(game.data)) { // Rectángulos de posiciones de ataque
                    batch->rect(Rect(pos.x + 4, pos.y + 4, 56, 56), Color("#ea4f36"));
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

        statics["helpMenu"]->draw(batch);
    } else if (*mode == 3) {
        statics["backgroundG"]->draw(batch); // Fondo
    }
}

void Assets::update(UmStatics statics, UmButtons buttons, VcPieces *pieces, VcNexuses *nexuses, Game *game, int *mode, FormationSet *formSet)
{
    for (auto & button : buttons) button.second->update();

    if (*mode == 0) {
        if (buttons["playMenuButton"]->isClicked() || Input::pressed(Key::P)) *mode = 1; // Play
        if (buttons["formsMenuButton"]->isClicked() || Input::pressed(Key::F))
            std::cout << "FORMACIONES" << std::endl; // Forms TODO
        if (buttons["exitMenuButton"]->isClicked() || Input::pressed(Key::Escape)) App::exit(); // Exit

        buttons["playMenuButton"]->setY((int) (buttons["playMenuButton"]->getY() +
                                               (328 - buttons["playMenuButton"]->getY()) * (double) Time::delta *
                                               4)); // Movimiento de los botones de inicio
        buttons["formsMenuButton"]->setY((int) (buttons["formsMenuButton"]->getY() +
                                                (444 - buttons["formsMenuButton"]->getY()) * (double) Time::delta * 4));
        buttons["exitMenuButton"]->setY((int) (buttons["exitMenuButton"]->getY() +
                                               (560 - buttons["exitMenuButton"]->getY()) * (double) Time::delta * 4));
    } else if (*mode == 1) {
        if (buttons["leftArrowButton"]->isClicked()) {
            if (formSet->index == 0) formSet->index = formSet->size - 1;
            else formSet->index--;
        }
        if (buttons["rightArrowButton"]->isClicked()) {
            if (formSet->index == formSet->size - 1) formSet->index = 0;
            else formSet->index++;
        }
        if (buttons["startButton"]->isClicked()) {
            *mode = 2;
            startGame(game, formSet->forms[formSet->index], formSet->forms[0]);
            loadPieceCoords(game, pieces);
        }
    } else if (*mode == 2) {
        for (auto & piece : *pieces) piece.update();

        for (auto & nexus : *nexuses) nexus.update();

        if (buttons["helpGameButton"]->isClicked() || Input::pressed(Key::H)) (statics)["helpMenu"]->swapActive();
        if (buttons["menuGameButton"]->isClicked()) {
            *mode = 0;
            loadPieceCoords(game, pieces);
        }
        if (buttons["exitGameButton"]->isClicked() || Input::pressed(Key::Escape)) App::exit();
        if (game->nexus1hp <= 0 || game->nexus2hp <= 0) *mode = 0;
    } else if (*mode == 3) {

    }
}

void loadPieceCoords(Game *gameRef, VcPieces *pieces)
{
    for (int i = 0; i < B_ROWS; i++) {
        for (int j = 0; j < B_COLUMNS; j++) {
            int dataCode = gameRef->data[i][j];
            if (dataCode >= 1 && dataCode <= 24) {
                for (auto & piece:*pieces) {
                    if (piece.id == dataCode) {
                        piece.setX(j * 64 + 416);
                        piece.setY(i * 64 + 64);
                    }
                }
            }
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

std::string getIconKey(int id)
{
    if (id >= 1 && id <= 4) {
        return "spearmanLIcon";
    } else if (id >= 5 && id <= 7) {
        return "wizardLIcon";
    } else if (id >= 8 && id <= 10) {
        return "assassinLIcon";
    } else if (id >= 11 && id <= 12) {
        return "golemLIcon";
    } else if (id >= 13 && id <= 16) {
        return "spearmanRIcon";
    } else if (id >= 17 && id <= 19) {
        return "wizardRIcon";
    } else if (id >= 20 && id <= 22) {
        return "assassinRIcon";
    } else if (id >= 23 && id <= 24) {
        return "golemRIcon";
    } else {
        return "golemRIcon";
    }
}

char * getPieceName(int id) {
    switch (id) {
        case 0: return (char*) "Spearman";
        case 1: return (char*) "Wizard";
        case 2: return (char*) "Assassin";
        case 3: return (char*) "Golem";
        default: return (char*) "";
    }
}

void renderFormation(Batch *batch, VcPieces *pieces, const char *formation, TextureRef blueNexusTex)
{
    int x = 548;
    int y = 104;
    for (int i = 0; i < FORM_LENGTH; i++) {
        if (formation[i] != 'e' && formation[i] != 'N') batch->tex(getPieceTexture(pieces, formation[i]), Vec2(x, y));
        else if (formation[i] == 'N') batch->tex(blueNexusTex, Vec2(x, y));

        if ((i+1) % 3 == 0) {
            y += 64;
            x = 548;
        }
        else {
            x += 64;
        }
    }
}

TextureRef getPieceTexture(VcPieces *pieces, char pieceLetter)
{
    int id;
    switch (pieceLetter) {
        case 's': id = 0; break;
        case 'w': id = 4; break;
        case 'a': id = 8; break;
        case 'g': id = 11; break;
        default: id = -1; break;
    }

    for (auto & piece:*pieces) {
        if (piece.id == id) return piece.texture;
    }
    return (*pieces)[0].texture;
}

void writeFormSetPos(Batch *batch, FormationSet *formSet)
{
    char index_str[4];
    sprintf(index_str, "%d", formSet->index + 1);
    char size_str[4];
    sprintf(size_str, "%d", formSet->size);
    strcat(index_str, "/");
    strcat(index_str, size_str);
    batch->str(font, index_str, Vec2(594, 50), Color::white);
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