#include "content.h"

void Assets::load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces)
{
    statics->push_back(StaticSprite(0, 0, "../data/img/background.png", true));
    statics->push_back(StaticSprite(320, 64, "../data/img/helpmenu.png", false));

    buttons->push_back(GuiButton(16, 16, 224, 64,
                                 "../data/img/helpButtonIdle.png", "../data/img/helpButtonPressed.png"));
    buttons->push_back(GuiButton(16, 96, 224, 64,
                                 "../data/img/exitButtonIdle.png", "../data/img/exitButtonPressed.png"));
}


void Assets::render(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces, Batch *batch)
{
    vector<StaticSprite>::iterator staticIt;
    for (staticIt = statics->begin(); staticIt != statics->end(); ++staticIt){
        staticIt->draw(batch);
    }

    vector<GuiButton>::iterator buttonIt;
    for (buttonIt = buttons->begin(); buttonIt != buttons->end(); buttonIt++) {
        buttonIt->update();
        buttonIt->draw(batch);
    }

    std::vector<PieceSprite>::iterator pieceIt;
    for (pieceIt = pieces->begin(); pieceIt != pieces->end(); pieceIt++) {
        pieceIt->update();
        pieceIt->draw(batch);
    }
}