#ifndef CHESS2_CONTENT_H
#define CHESS2_CONTENT_H

#include <blah.h>
#include <list>
#include <map>
#include "gui/staticSprite.h"
#include "gui/guiButton.h"
#include "gui/pieceSprite.h"
extern "C" {
    #include "game/game.h"
};

using namespace Blah;
using std::vector;

namespace Assets {
    void load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces);
    void render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, Batch *batch, Game game);
    void updateGame(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, Game *game);
    void updateMenu(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces);
}

#endif //CHESS2_CONTENT_H
