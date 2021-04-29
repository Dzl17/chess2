#ifndef CHESS2_DRAGGABLEPIECESPRITE_H
#define CHESS2_DRAGGABLEPIECESPRITE_H

#include "sprite.h"

class DraggablePieceSprite :  public Sprite{
private:
    int ogX, ogY;
public:
    DraggablePieceSprite(int x, int y, const String& texturePath);

    bool grabbed;
    static bool grabFlag;

    void update() override;
    void draw(Batch *batch) override;
};


#endif