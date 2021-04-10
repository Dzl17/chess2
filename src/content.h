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
using std::vector;

namespace Assets {
    void load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Game game, int *mode);
    void render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Batch *batch, Game game, int *mode);
    void update(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, vector <NexusSprite> *nexuses, Batch *batch, Game *game, int *mode);
}

#endif //CHESS2_CONTENT_H
