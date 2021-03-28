#ifndef CHESS2_STATICSPRITE_H
#define CHESS2_STATICSPRITE_H

#include "sprite.h"

class StaticSprite : public Sprite{
public:
    StaticSprite();
    void load(int x, int y, const String& texturePath);
    void update() override;
    void draw(Batch *batch) override;
};


#endif //CHESS2_STATICSPRITE_H
