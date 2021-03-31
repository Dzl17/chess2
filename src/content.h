#ifndef CHESS2_CONTENT_H
#define CHESS2_CONTENT_H

#include <blah.h>
#include <list>
#include <map>
#include "gui/staticSprite.h"
#include "gui/guiButton.h"
#include "gui/pieceSprite.h"

using namespace Blah;

namespace Assets {
    void load(std::list<StaticSprite> *statics, std::map<int, GuiButton> *buttons, std::map<int, PieceSprite> *pieces);
    void render(std::list<StaticSprite> *statics, std::map<int, GuiButton> *buttons, std::map<int, PieceSprite> *pieces, Batch *batch);
}

#endif //CHESS2_CONTENT_H
