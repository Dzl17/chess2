#ifndef CHESS2_STATICSPRITE_H
#define CHESS2_STATICSPRITE_H

#include "sprite.h"

class StaticSprite : public Sprite{
public:
    StaticSprite(int x, int y, const String& texturePath, bool active);
    bool active;
    void swapActive();
    void update() override;
    void draw(Batch *batch) override;
};


#endif //CHESS2_STATICSPRITE_H
