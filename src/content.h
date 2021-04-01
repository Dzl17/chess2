#ifndef CHESS2_CONTENT_H
#define CHESS2_CONTENT_H

#include <blah.h>
#include <list>
#include <map>
#include "gui/staticSprite.h"
#include "gui/guiButton.h"
#include "gui/pieceSprite.h"

using namespace Blah;
using std::vector;

namespace Assets {
    void load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces);
    void render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, Batch *batch);
}

#endif //CHESS2_CONTENT_H
