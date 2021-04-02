#include "content.h"

void Assets::load(vector<StaticSprite> *statics, vector<GuiButton> *buttons, vector<PieceSprite> *pieces)
{
    statics->push_back(StaticSprite(0, 0, "../data/img/background.png", true));
    statics->push_back(StaticSprite(320, 64, "../data/img/helpmenu.png", false));

    buttons->push_back(GuiButton(16, 16, 224, 64,
                                 "../data/img/helpButtonIdle.png", "../data/img/helpButtonPressed.png"));
    buttons->push_back(GuiButton(16, 96, 224, 64,
                                 "../data/img/exitButtonIdle.png", "../data/img/exitButtonPressed.png"));

    pieces->push_back(PieceSprite(416, 128, "../data/img/units/assassinL.png"));
    pieces->push_back(PieceSprite(480, 128, "../data/img/units/wizardL.png"));
    pieces->push_back(PieceSprite(416, 192, "../data/img/units/spearmanL.png"));
    pieces->push_back(PieceSprite(480, 192, "../data/img/units/golemL.png"));

    pieces->push_back(PieceSprite(992, 128, "../data/img/units/assassinR.png"));
    pieces->push_back(PieceSprite(1056, 128, "../data/img/units/wizardR.png"));
    pieces->push_back(PieceSprite(992, 192, "../data/img/units/spearmanR.png"));
    pieces->push_back(PieceSprite(1056, 192, "../data/img/units/golemR.png"));
}

// TODO orden de renderizado
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