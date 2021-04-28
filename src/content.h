#ifndef CHESS2_CONTENT_H
#define CHESS2_CONTENT_H

#include <blah.h>
#include <list>
#include "gui/staticSprite.h"
#include "gui/guiButton.h"
#include "gui/pieceSprite.h"
#include "gui/nexusSprite.h"
extern "C" {
    #include "game/game.h"
};

using namespace Blah;

using UmStatics = std::unordered_map<std::string, StaticSprite*>;
using UmButtons = std::unordered_map<std::string, GuiButton*>;
using VcPieces = std::vector<PieceSprite>;
using VcNexuses = std::vector<NexusSprite>;

typedef struct { // TODO sacar de BD
    char **forms;
    int size, index;
} FormationSet;

/*
 * La variable 'mode' denota qué pantalla debe dibujarse:
 * 0 -  Menú principal
 * 1 -  Selección de formación
 * 2 -  Juego principal
 * 3+ - Formaciones
 */

namespace Assets {
    void load(UmStatics *statics, UmButtons *buttons, VcPieces *pieces, VcNexuses *nexuses, Game *game, int *mode, FormationSet *formSet);
    void render(UmStatics statics, UmButtons buttons, VcPieces *pieces, VcNexuses *nexuses, Game  game, int *mode, FormationSet *formSet, Batch *batch);
    void update(UmStatics statics, UmButtons buttons, VcPieces *pieces, VcNexuses *nexuses, Game *game, int *mode, FormationSet *formSet);
}

namespace Login {
    void runSetup();
}

#endif //CHESS2_CONTENT_H
