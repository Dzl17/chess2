#ifndef CHESS2_CONTENT_H
#define CHESS2_CONTENT_H

#include <blah.h>
#include <list>
#include "gui/staticSprite.h"
#include "gui/guiButton.h"
#include "gui/pieceSprite.h"
#include "gui/nexusSprite.h"
#include "dbmanager.h"
#include "user.h"

extern "C" {
    #include "game/game.h"
}

enum Screen {
    kMainMenu,                  // Menú principal
    kFormSelectionMenu,         // Selección de formación para jugar
    kMainGame,                  // Juego principal
    kFormEditionSelectionMenu,  // Selección de formación para modificar
    kFormEditionMenu,           // Edición de formación
    kUserInfoMenu               // Información de usuario
};

using namespace Blah;

using UmStatics = std::unordered_map<std::string, StaticSprite*>;
using UmButtons = std::unordered_map<std::string, GuiButton*>;
using VcPieces = std::vector<PieceSprite>;
using VcNexuses = std::vector<NexusSprite>;

namespace Assets {
    void load(UmStatics& statics, UmButtons& buttons, VcPieces& pieces, VcNexuses& nexuses, Game *game, Screen& screen, User& user);
    void render(UmStatics statics, UmButtons buttons, VcPieces& pieces, VcNexuses& nexuses, Game  game, Screen& screen, User& user, Batch *batch);
    void update(UmStatics statics, UmButtons buttons, VcPieces& pieces, VcNexuses& nexuses, Game *game, Screen& screen, User& user);
}

namespace Login {
    User *runSetup(DBManager& dbManager, bool& exit);
}

#endif
