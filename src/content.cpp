#include "content.h"

void Assets::load(std::list<StaticSprite> *statics, std::map<int, GuiButton> *buttons, std::map<int, PieceSprite> *pieces)
{
    statics->push_back(StaticSprite(0, 0, "../data/img/background.png"));

    buttons->insert(std::pair<int, GuiButton>(
            1, // Test Button
            GuiButton(32, 16, 192, 64,"../data/img/testButtonIdle.png", "../data/img/testButtonPressed.png")));
}


void Assets::render(std::list<StaticSprite> *statics, std::map<int, GuiButton> *buttons, std::map<int, PieceSprite> *pieces, Batch *batch)
{
    std::list<StaticSprite>::iterator staticIt;
    for (staticIt = statics->begin(); staticIt != statics->end(); ++staticIt){
        staticIt->draw(batch);
    }

    std::map<int, GuiButton>::iterator buttonIt;
    for (buttonIt = buttons->begin(); buttonIt != buttons->end(); buttonIt++) {
        buttonIt->second.update();
        buttonIt->second.draw(batch);
    }

    std::map<int, PieceSprite>::iterator pieceIt;
    for (pieceIt = pieces->begin(); pieceIt != pieces->end(); pieceIt++) {
        pieceIt->second.update();
        pieceIt->second.draw(batch);
    }
}