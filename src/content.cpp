#include <map>
#include "content.h"
#include "gui/draggablePieceSprite.h"

void loadButtons(UmButtons& buttons);
void loadStatics(UmStatics& statics);
void loadPieceCoords(Game *gameRef, VcPieces& pieces);
void loadDPSprites();
void loadDPSPositions();
void resetDPSprites();

void renderPieceData(Batch *batch, VcPieces& pieces, UmStatics& statics, Game game);
void renderFormation(Batch *batch, VcPieces& pieces, const char *formation, const TextureRef& blueNexusTex);

String getSpritePath(int id);
std::string getIconKey(int id);
TextureRef getPieceTexture(VcPieces& pieces, char pieceLetter);
char *getPieceName(int id);
bool isFormValid(const char *form);
void saveCurrentGame(Game *game);
void writeFormSetPos(Batch *batch, FormationSet& formSet);
void writePieceHp(Batch *batch, PieceSprite& piece);
void writePieceDmg(Batch *batch, PieceSprite& piece);
void writeUserData(Batch *batch, User user);

SpriteFont font;
std::map<int, DraggablePieceSprite*> dpSprites;
bool useBrownBackground = false;
double error_timer = 0;

void Assets::load(UmStatics& statics, UmButtons& buttons, VcPieces& pieces, VcNexuses& nexuses, Game *game, Screen& screen, User& user)
{
    font = SpriteFont("data/fonts/dogica.ttf", 32);
    loadButtons(buttons);
    loadStatics(statics);
    loadDPSprites();
    loadCollisionPositions();
    for (int i = 1; i <= 24; i++) pieces.push_back(PieceSprite(0,0, i,getSpritePath(i), game));
    nexuses.push_back(NexusSprite( 416, 256, "data/img/nexusL.png"));
    nexuses.push_back(NexusSprite(1056, 256, "data/img/nexusR.png"));
}

void Assets::render(UmStatics statics, UmButtons buttons, VcPieces&pieces, VcNexuses&nexuses, Game game, Screen& screen, User& user, Batch *batch)
{
    if (screen == kMainMenu) { // Menú principal
        statics["mainMenu"]->draw(batch); // Fondo
        buttons["playMenuButton"]->draw(batch);
        buttons["formsMenuButton"]->draw(batch);
        if (useBrownBackground) buttons["pressedSkinButton"]->draw(batch);
        else buttons["skinButton"]->draw(batch);
        buttons["userButton"]->draw(batch);
        buttons["exitMenuButton"]->draw(batch);
    }
    else if (screen == kFormSelectionMenu) { // Selección de formación
        statics["choosingBackground"]->draw(batch);
        buttons["leftArrowButton"]->draw(batch);
        buttons["rightArrowButton"]->draw(batch);
        buttons["startButton"]->draw(batch);
        buttons["backButton"]->draw(batch);
        renderFormation(batch, pieces, user.formationSet.forms[user.formationSet.index], nexuses[0].texture);
        writeFormSetPos(batch, user.formationSet);
        if (Time::seconds < error_timer) {
            batch->str(font, "Invalid", Vec2(120, 600), Color::white);
            batch->str(font, "formation.", Vec2(124, 640), Color::white);
        }
    }
    else if (screen == kMainGame) {
        if (useBrownBackground) statics["backgroundB"]->draw(batch); // Fondo
        else statics["backgroundG"]->draw(batch); // Fondo
        buttons["helpGameButton"]->draw(batch);
        buttons["loadGameButton"]->draw(batch);
        buttons["saveGameButton"]->draw(batch);
        buttons["menuGameButton"]->draw(batch);
        buttons["exitGameButton"]->draw(batch);

        // Vida de los nexos
        batch->rect(Rect(404, 700, 8, (float)game.nexus1hp * (-112) / NEXUS_HP), Color("4d9be6")); // Vida azul
        batch->rect(Rect(1124, 700, 8, (float)game.nexus2hp * (-112) / NEXUS_HP), Color("ea4f36")); // Vida roja

        // Turno de jugador TODO
        if (game.turn % 2 == 0) batch->rect(Rect(416, 256, 64, 64), Color("#8a0da6"));
        else batch->rect(Rect(1056, 256, 64, 64), Color("#8a0da6"));

        renderPieceData(batch, pieces, statics, game);

        for (auto & piece : pieces) piece.draw(batch);
        for (auto & nexus : nexuses) nexus.draw(batch);

        statics["helpMenu"]->draw(batch);
    }
    else if (screen == kFormEditionSelectionMenu) {
        statics["choosingBackground"]->draw(batch);
        buttons["leftArrowButton"]->draw(batch);
        buttons["rightArrowButton"]->draw(batch);
        buttons["editButton"]->draw(batch);
        buttons["backButton"]->draw(batch);
        renderFormation(batch, pieces, user.formationSet.forms[user.formationSet.index], nexuses[0].texture);
        writeFormSetPos(batch, user.formationSet);
    }
    else if (screen == kFormEditionMenu) {
        statics["formsBackground"]->draw(batch);
        buttons["saveButton"]->draw(batch);
        buttons["backButton"]->draw(batch);
        buttons["resetButton"]->draw(batch);
        batch->tex(nexuses[0].texture, Vec2(544, 296));
        for (auto & piece:dpSprites) piece.second->draw(batch);
        writeFormSetPos(batch, user.formationSet);
    }
    else if (screen == kUserInfoMenu) {
        statics["userBackground"]->draw(batch); // Fondo
        buttons["backButton"]->draw(batch);
        writeUserData(batch, user);
    }
}

void Assets::update(UmStatics statics, UmButtons buttons, VcPieces& pieces, VcNexuses& nexuses, Game *game, Screen& screen, User& user)
{
    for (auto & button : buttons) button.second->update();

    if (screen == kMainMenu) {
        if (buttons["playMenuButton"]->isClicked() || Input::pressed(Key::P)) screen = kFormSelectionMenu; // Play
        if (buttons["formsMenuButton"]->isClicked() || Input::pressed(Key::F)) {
            screen = kFormEditionSelectionMenu; // Forms
            user.formationSet.index = 4;
        }
        if (useBrownBackground) {
            if (buttons["pressedSkinButton"]->isClicked() || Input::pressed(Key::S)) useBrownBackground = false;
        }
        else {
            if (buttons["skinButton"]->isClicked() || Input::pressed(Key::S)) useBrownBackground = true;
        }
        if (buttons["userButton"]->isClicked() || Input::pressed(Key::U)) screen = kUserInfoMenu; // Exit
        if (buttons["exitMenuButton"]->isClicked() || Input::pressed(Key::Escape)) App::exit(); // Exit

        buttons["playMenuButton"]->setY((int) (buttons["playMenuButton"]->getY() +
                                               (328 - buttons["playMenuButton"]->getY()) * (double) Time::delta *
                                               4)); // Movimiento de los botones de inicio
        buttons["formsMenuButton"]->setY((int) (buttons["formsMenuButton"]->getY() +
                                                (444 - buttons["formsMenuButton"]->getY()) * (double) Time::delta * 4));
        buttons["skinButton"]->setY((int) (buttons["skinButton"]->getY() +
                                               (560 - buttons["skinButton"]->getY()) * (double) Time::delta * 4));
        buttons["pressedSkinButton"]->setY((int) (buttons["skinButton"]->getY() +
                                               (560 - buttons["skinButton"]->getY()) * (double) Time::delta * 4));
        buttons["userButton"]->setY((int) (buttons["userButton"]->getY() +
                                               (560 - buttons["userButton"]->getY()) * (double) Time::delta * 4));
        buttons["exitMenuButton"]->setY((int) (buttons["exitMenuButton"]->getY() +
                                               (560 - buttons["exitMenuButton"]->getY()) * (double) Time::delta * 4));
    }
    else if (screen == kFormSelectionMenu) {
        if (buttons["leftArrowButton"]->isClicked()) {
            if (user.formationSet.index == 0) user.formationSet.index = user.formationSet.size - 1;
            else user.formationSet.index--;
        }
        if (buttons["rightArrowButton"]->isClicked()) {
            if (user.formationSet.index == user.formationSet.size - 1) user.formationSet.index = 0;
            else user.formationSet.index++;
        }
        if (buttons["startButton"]->isClicked()) {
            if (isFormValid(user.formationSet.forms[user.formationSet.index])) {
                screen = kMainGame;
                startGame(game, user.formationSet.forms[user.formationSet.index], user.formationSet.forms[0]);
                loadPieceCoords(game, pieces);
            } else {
                error_timer = Time::seconds + 2;
            }
        }
        if (buttons["backButton"]->isClicked()) {
            screen = kMainMenu;
        }
    }
    else if (screen == kMainGame) {
        for (auto & piece : pieces) piece.update();

        for (auto & nexus : nexuses) nexus.update();

        if (buttons["helpGameButton"]->isClicked() || Input::pressed(Key::H)) statics["helpMenu"]->swapActive();
        if (buttons["loadGameButton"]->isClicked()) {

        }
        if (buttons["saveGameButton"]->isClicked()) {
            saveCurrentGame(game);
        }
        if (buttons["menuGameButton"]->isClicked()) {
            screen = kMainMenu;
            loadPieceCoords(game, pieces);
        }
        if (buttons["exitGameButton"]->isClicked() || Input::pressed(Key::Escape)) App::exit();
        if (game->nexus1hp <= 0 || game->nexus2hp <= 0) {
            if (game->nexus2hp <= 0) user.addWin();
            else user.addLose();
            user.calculateElo(1000, game->nexus2hp <= 0);
            screen = kMainMenu;
        }
    }
    else if (screen == kFormEditionSelectionMenu) {
        if (buttons["leftArrowButton"]->isClicked()) {
            if (user.formationSet.index == 4) user.formationSet.index = user.formationSet.size - 1;
            else user.formationSet.index--;
        }
        if (buttons["rightArrowButton"]->isClicked()) {
            if (user.formationSet.index == user.formationSet.size - 1) user.formationSet.index = 4;
            else user.formationSet.index++;
        }
        if (buttons["editButton"]->isClicked()) {
            screen = kFormEditionMenu;
            strncpy(DraggablePieceSprite::formBuffer, user.formationSet.forms[user.formationSet.index], 21);
            loadDPSPositions();
        }
        if (buttons["backButton"]->isClicked()) {
            screen = kMainMenu;
        }
    }
    else if (screen == kFormEditionMenu) {
        for (auto & piece:dpSprites) piece.second->update();
        if (buttons["saveButton"]->isClicked()) {
            user.formationSet.forms[user.formationSet.index] = DraggablePieceSprite::formBuffer;
            screen = kMainMenu;
        }
        if (buttons["resetButton"]->isClicked()) {
            DraggablePieceSprite::resetFormBuffer();
            resetDPSprites();
        }
        if (buttons["backButton"]->isClicked()) {
            screen = kFormEditionSelectionMenu;
        }
        if (Input::pressed(Key::Enter)) screen = kMainMenu;
        if (Input::pressed(Key::Escape)) App::exit();
    }
    else if (screen == kUserInfoMenu) {
        if (Input::pressed(Key::Escape)) App::exit();
        if (buttons["backButton"]->isClicked() ||Input::pressed(Key::B)) screen = kMainMenu;
    }
}

void loadButtons(UmButtons& buttons)
{
    buttons.insert({"playMenuButton",   new GuiButton(512, 1128, 256, 108, // Play (menu)
                                                    "data/img/buttons/playMenuButtonIdle.png", "data/img/buttons/playMenuButtonPressed.png")});
    buttons.insert({"formsMenuButton",  new GuiButton(512, 1544, 256, 108, // Forms (menu)
                                                     "data/img/buttons/formsMenuButtonIdle.png", "data/img/buttons/formsMenuButtonPressed.png")});
    buttons.insert({"skinButton",       new GuiButton(512, 1960, 80, 108, // Exit (menu)
                                                      "data/img/buttons/skinButtonIdle.png", "data/img/buttons/skinButtonPressed.png")});
    buttons.insert({"pressedSkinButton",       new GuiButton(512, 1960, 80, 108, // Exit (menu)
                                                      "data/img/buttons/skinButtonPressed.png", "data/img/buttons/skinButtonPressed.png")});
    buttons.insert({"userButton",       new GuiButton(600, 1960, 80, 108, // Exit (menu)
                                                      "data/img/buttons/userButtonIdle.png", "data/img/buttons/userButtonPressed.png")});
    buttons.insert({"exitMenuButton",   new GuiButton(688, 1960, 80, 108, // Exit (menu)
                                                    "data/img/buttons/smallExitButtonIdle.png", "data/img/buttons/smallExitButtonPressed.png")});

    buttons.insert({"leftArrowButton",  new GuiButton(352, 264, 128, 128,
                                                     "data/img/buttons/leftArrowIdle.png", "data/img/buttons/leftArrowPressed.png")});
    buttons.insert({"rightArrowButton", new GuiButton(800, 264, 128, 128,
                                                      "data/img/buttons/rightArrowIdle.png", "data/img/buttons/rightArrowPressed.png")});
    buttons.insert({"startButton",      new GuiButton(512, 586, 256, 108,
                                                 "data/img/buttons/startButtonIdle.png", "data/img/buttons/startButtonPressed.png")});
    buttons.insert({"editButton",       new GuiButton(512, 586, 256, 108,
                                                 "data/img/buttons/editButtonIdle.png", "data/img/buttons/editButtonPressed.png")});
    buttons.insert({"saveButton",       new GuiButton(512, 586, 256, 108,
                                                "data/img/buttons/saveButtonIdle.png", "data/img/buttons/saveButtonPressed.png")});
    buttons.insert({"resetButton",      new GuiButton(436, 602,  64,  76,
                                                "data/img/buttons/resetButtonIdle.png", "data/img/buttons/resetButtonPressed.png")});
    buttons.insert({"backButton",       new GuiButton(780, 602,  64,  76,
                                                "data/img/buttons/backButtonIdle.png", "data/img/buttons/backButtonPressed.png")});

    buttons.insert({"helpGameButton",   new GuiButton( 16,  16, 224,  80,
                                                    "data/img/buttons/helpButtonIdle.png", "data/img/buttons/helpButtonPressed.png")});
    buttons.insert({"loadGameButton",   new GuiButton( 16, 144, 224,  80,
                                                       "data/img/buttons/loadButtonIdle.png", "data/img/buttons/loadButtonPressed.png")});
    buttons.insert({"saveGameButton",   new GuiButton( 16, 240, 224,  80,
                                                       "data/img/buttons/saveGameButtonIdle.png", "data/img/buttons/saveGameButtonPressed.png")});
    buttons.insert({"menuGameButton",   new GuiButton( 16, 368, 224,  80,
                                                    "data/img/buttons/menuButtonIdle.png", "data/img/buttons/menuButtonPressed.png")});
    buttons.insert({"exitGameButton",   new GuiButton( 16, 464, 224,  80,
                                                    "data/img/buttons/exitButtonIdle.png", "data/img/buttons/exitButtonPressed.png")});
}

void loadStatics(UmStatics& statics)
{
    statics.insert({"backgroundG",       new StaticSprite(0,     0, "data/img/backgroundG.png",         true)});
    statics.insert({"backgroundB",       new StaticSprite(0,     0, "data/img/backgroundB.png",         true)});
    statics.insert({"formsBackground",   new StaticSprite(0,     0, "data/img/formsBackground.png",     true)});
    statics.insert({"choosingBackground",new StaticSprite(0,     0, "data/img/choosingBackground.png",  true)});
    statics.insert({"userBackground",    new StaticSprite(0,     0, "data/img/userBackground.png",      true)});
    statics.insert({"emptyBackground",   new StaticSprite(0,     0, "data/img/emptyBackground.png",     true)});
    statics.insert({"helpMenu",          new StaticSprite(320,  64, "data/img/helpmenu.png",            false)});
    statics.insert({"spearmanLIcon",     new StaticSprite(480, 556, "data/img/icons/spearmanLIcon.png", true)});
    statics.insert({"spearmanRIcon",     new StaticSprite(480, 556, "data/img/icons/spearmanRIcon.png", true)});
    statics.insert({"wizardLIcon",       new StaticSprite(480, 556, "data/img/icons/wizardLIcon.png",   true)});
    statics.insert({"wizardRIcon",       new StaticSprite(480, 556, "data/img/icons/wizardRIcon.png",   true)});
    statics.insert({"assassinLIcon",     new StaticSprite(480, 556, "data/img/icons/assassinLIcon.png", true)});
    statics.insert({"assassinRIcon",     new StaticSprite(480, 556, "data/img/icons/assassinRIcon.png", true)});
    statics.insert({"golemLIcon",        new StaticSprite(480, 556, "data/img/icons/golemLIcon.png",    true)});
    statics.insert({"golemRIcon",        new StaticSprite(480, 556, "data/img/icons/golemRIcon.png",    true)});
    statics.insert({"mainMenu",          new StaticSprite(0,     0, "data/img/mainMenu.png",            true)});
}

void loadPieceCoords(Game *gameRef, VcPieces& pieces)
{
    for (int i = 0; i < B_ROWS; i++) {
        for (int j = 0; j < B_COLUMNS; j++) {
            int dataCode = gameRef->data[i][j];
            if (dataCode >= 1 && dataCode <= 24) {
                for (auto & piece:pieces) {
                    if (piece.id == dataCode) {
                        piece.setX(j * 64 + 416);
                        piece.setY(i * 64 + 64);
                    }
                }
            }
        }
    }
}

void loadDPSprites()
{
    int x = 128;
    int y = 176;
    for (int i = 1; i <= 4; i++) {
        dpSprites.insert({i, new DraggablePieceSprite(x,y,i,getSpritePath(i))});
        if (i == 3) {
            x = 128;
            y += 80;
        } else {
            x += 80;
        }
    }
    dpSprites.insert({11, new DraggablePieceSprite(x,y,11,getSpritePath(11))});
    x += 80;
    dpSprites.insert({12, new DraggablePieceSprite(x,y,12,getSpritePath(12))});
    x = 128;
    y += 80;
    for (int i = 5; i <= 10; i++) {
        dpSprites.insert({i, new DraggablePieceSprite(x,y,i,getSpritePath(i))});
        if (i == 7 || i == 10) {
            x = 128;
            y += 80;
        } else {
            x += 80;
        }
    }
}

void loadDPSPositions()
{
    Vec2 collBuffer[FORM_LENGTH];
    int x = 544;
    int y = 104;
    for (int i = 0; i < FORM_LENGTH; i++) {
        collBuffer[i] = Vec2(x, y);
        if ((i+1)%3 == 0) {
            x = 544;
            y += 64;
        } else {
            x += 64;
        }
    }

    int s = 1;
    int w = 5;
    int a = 8;
    int g = 11;
    for (int i = 0; i < FORM_LENGTH; i++) {
        switch(DraggablePieceSprite::formBuffer[i]) {
            case 's':
                for (auto & dps:dpSprites) {
                    if (dps.second->getId() == s) {
                        dps.second->setX((int) collBuffer[i].x);
                        dps.second->setY((int) collBuffer[i].y);
                        dps.second->setCurrIndex(i);
                        s++;
                        break;
                    }
                }
                break;
            case 'w':
                for (auto & dps:dpSprites) {
                    if (dps.second->getId() == w) {
                        dps.second->setX((int) collBuffer[i].x);
                        dps.second->setY((int) collBuffer[i].y);
                        dps.second->setCurrIndex(i);
                        w++;
                        break;
                    }
                }
                break;
            case 'a':
                for (auto & dps:dpSprites) {
                    if (dps.second->getId() == a) {
                        dps.second->setX((int) collBuffer[i].x);
                        dps.second->setY((int) collBuffer[i].y);
                        dps.second->setCurrIndex(i);
                        a++;
                        break;
                    }
                }
                break;
            case 'g':
                for (auto & dps:dpSprites) {
                    if (dps.second->getId() == g) {
                        dps.second->setX((int) collBuffer[i].x);
                        dps.second->setY((int) collBuffer[i].y);
                        dps.second->setCurrIndex(i);
                        g++;
                        break;
                    }
                }
                break;
            default:
                continue;
        }
    }
}

void resetDPSprites()
{
    int x = 128;
    int y = 176;
    for (int i = 1; i <= 4; i++) {
        dpSprites[i]->setX(x);
        dpSprites[i]->setY(y);
        if (i == 3) {
            x = 128;
            y += 80;
        } else {
            x += 80;
        }
    }
    dpSprites[11]->setX(x);
    dpSprites[11]->setY(y);
    x += 80;
    dpSprites[12]->setX(x);
    dpSprites[12]->setY(y);
    x = 128;
    y += 80;
    for (int i = 5; i <= 10; i++) {
        dpSprites[i]->setX(x);
        dpSprites[i]->setY(y);
        if (i == 7 || i == 10) {
            x = 128;
            y += 80;
        } else {
            x += 80;
        }
    }
}

void saveCurrentGame(Game *game)
{
    int savePieces[24][4];
    for (int i = 0; i < 24; ++i) {  // Se guardan las posiciones de las piezas
        savePieces[i][0] = game->pieces[i].id;
        savePieces[i][1] = game->pieces[i].hp;
        for (int j = 0; j < B_ROWS; j++) {
            for (int k = 0; k < B_COLUMNS; k++) {
                if (game->data[j][k] == game->pieces[i].id) {
                    savePieces[i][2] = j;
                    savePieces[i][3] = k;
                    break;
                }
            }
        }
    }
    saveGame(game->turn, game->nexus1hp, game->nexus2hp, savePieces);
}

String getSpritePath(int id)
{
    if (id >= 1 && id <= 4) {
        return "data/img/units/spearmanL.png";
    } else if (id >= 5 && id <= 7) {
        return "data/img/units/wizardL.png";
    } else if (id >= 8 && id <= 10) {
        return "data/img/units/assassinL.png";
    } else if (id >= 11 && id <= 12) {
        return "data/img/units/golemL.png";
    } else if (id >= 13 && id <= 16) {
        return "data/img/units/spearmanR.png";
    } else if (id >= 17 && id <= 19) {
        return "data/img/units/wizardR.png";
    } else if (id >= 20 && id <= 22) {
        return "data/img/units/assassinR.png";
    } else if (id >= 23 && id <= 24) {
        return "data/img/units/golemR.png";
    } else {
        return "data/img/boredlion.png";
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

bool isFormValid(const char *form)
{
    int s = 0;
    int a = 0;
    int w = 0;
    int g = 0;
    for (int i = 0; i < FORM_LENGTH; i++) {
        switch (form[i]) {
            case 's': s++; break;
            case 'a': a++; break;
            case 'w': w++; break;
            case 'g': g++; break;
        }
    }
    return s == 4 && a == 3 && w == 3 && g == 2 && form[9] == 'N';
}

void renderPieceData(Batch *batch, VcPieces& pieces, UmStatics& statics, Game game)
{
    for (auto & piece : pieces) {
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
}

void renderFormation(Batch *batch, VcPieces& pieces, const char *formation, const TextureRef& blueNexusTex)
{
    int x = 544;
    int y = 104;
    for (int i = 0; i < FORM_LENGTH; i++) {
        if (formation[i] != 'e' && formation[i] != 'N') batch->tex(getPieceTexture(pieces, formation[i]), Vec2(x, y));
        else if (formation[i] == 'N') batch->tex(blueNexusTex, Vec2(x, y));

        if ((i+1) % 3 == 0) {
            y += 64;
            x = 544;
        }
        else {
            x += 64;
        }
    }
}

TextureRef getPieceTexture(VcPieces& pieces, char pieceLetter)
{
    int id;
    switch (pieceLetter) {
        case 's': id = 1; break;
        case 'w': id = 5; break;
        case 'a': id = 8; break;
        case 'g': id = 11; break;
        default: id = -1; break;
    }

    for (auto & piece:pieces) {
        if (piece.id == id) return piece.texture;
    }
    return pieces[0].texture;
}

void writeFormSetPos(Batch *batch, FormationSet& formSet)
{
    char index_str[4];
    sprintf(index_str, "%d", formSet.index + 1);
    char size_str[4];
    sprintf(size_str, "%d", formSet.size);
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

void writeUserData(Batch *batch, User user)
{
    int offset = 0;
    if (strlen(user.getUsername()) <= 14) {
        char usr_str[64] = "User: ";
        strcat(usr_str, user.getUsername());
        batch->str(font, usr_str, Vec2(416, 226), Color::white);
    } else {
        offset = 44;
        char usr_str_1[64] = "User: ";
        char usr_sub_1[8];
        strncpy(usr_sub_1, user.getUsername(), 7);
        strcat(usr_str_1, usr_sub_1);
        strcat(usr_str_1, "-");
        batch->str(font, usr_str_1, Vec2(416, 226), Color::white);

        char usr_str_2[64] = "";
        char usr_sub_2[14];
        std::copy(user.getUsername() + 7, user.getUsername() + strlen(user.getUsername()), usr_sub_2);
        strcat(usr_str_2, usr_sub_2);
        batch->str(font, usr_str_2, Vec2(416, 226 + offset), Color::white);
    }

    char elo_str[64] = "Elo: ";
    char elo_num[8];
    sprintf(elo_num, "%d", user.getElo());
    strcat(elo_str, elo_num);
    batch->str(font, elo_str, Vec2(416, 270 + offset), Color::white);

    char wins_str[64] = "Wins: ";
    char wins_num[8];
    sprintf(wins_num, "%d", user.getWins());
    strcat(wins_str, wins_num);
    batch->str(font, wins_str, Vec2(420, 314 + offset), Color::white);

    char losses_str[64] = "Losses: ";
    char losses_num[8];
    sprintf(losses_num, "%d", user.getLosses());
    strcat(losses_str, losses_num);
    batch->str(font, losses_str, Vec2(412, 358 + offset), Color::white);
}

User* Login::runSetup(DBManager& dbManager, bool& exit)
{
    int op = 0;
    std::cout << "Choose an option:" << std::endl;
    std::cout << "1) Log in" << std::endl;
    std::cout << "2) Register" << std::endl;
    std::cout << "3) Exit" << std::endl;
    std::cin >> op;
    char *username = new char[20];
    char *password = new char[20];
    if (op == 1) {
        do {
            std::cout << "Username: ";
            std::cin >> username;
        } while (strlen(username) <= 0);
        if (!dbManager.userExists(username)) {
            std::cout << "User " << username << " not found." << std::endl;
            delete[] username;
            delete[] password;
            return nullptr;
        }

        do {
            std::cout << "Password: ";
            std::cin >> password;
        } while (strlen(password) <= 0);
        if (dbManager.verifyUser(username, password)) {
            User *user;
            user = dbManager.loadUser(username);
            std::cout << "Welcome, " << user->getUsername() << "." << std::endl;
            delete[] username;
            delete[] password;
            return user;
        } else {
            std::cout << "Password is wrong for user '" << username << "'." << std::endl;
            return nullptr;
        }
    } else if (op == 2){
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << "Password: ";
        std::cin >> password;
        if (!dbManager.userExists(username)) {
            dbManager.addNewUser(username, password);
            std::cout << "User " << username << " registered." << std::endl;
            if (dbManager.userExists(username)) return dbManager.loadUser(username);
            else return nullptr;
        }
        else {
            std::cout << "Username " << username << " already exists." << std::endl;
            return nullptr;
        }
    } else {
        exit = true;
        return nullptr;
    }
}