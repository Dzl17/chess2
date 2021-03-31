#ifndef CHESS2_PIECESPRITE_H
#define CHESS2_PIECESPRITE_H

#include "sprite.h"

class PieceSprite : public Sprite{
public:
    void update() override;
    void draw(Batch *batch) override;
};


#endif //CHESS2_PIECESPRITE_H
