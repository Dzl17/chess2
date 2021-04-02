#ifndef CHESS2_PIECESPRITE_H
#define CHESS2_PIECESPRITE_H

#include "sprite.h"

class PieceSprite : public Sprite {
public:
    PieceSprite(int x, int y, const String& texturePath);
    void update() override;
    void draw(Batch *batch) override;
};


#endif //CHESS2_PIECESPRITE_H
