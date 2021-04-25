#ifndef CHESS2_NEXUSSPRITE_H
#define CHESS2_NEXUSSPRITE_H

#include "sprite.h"

class NexusSprite : public Sprite{
private:
    float deltaCounter;
public:
    NexusSprite(int x, int y, const String& texturePath);
    void update() override;
    void draw(Batch *batch) override;
};


#endif //CHESS2_NEXUSSPRITE_H
