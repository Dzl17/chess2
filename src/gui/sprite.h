#ifndef CHESS2_SPRITE_H
#define CHESS2_SPRITE_H

#include <blah.h>
#include <iostream>
extern "C" {
    #include "../game/chess2.h"
};

using namespace Blah;

class Sprite {
private:
    int x, y;
    friend std::ostream& operator<<(std::ostream &strm, const Sprite &sprite);
protected:
    Sprite() = default;
public:
    TextureRef texture;
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    virtual void draw(Batch *batch) = 0;
};


#endif //CHESS2_SPRITE_H
