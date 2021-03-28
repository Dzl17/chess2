#ifndef CHESS2_SPRITE_H
#define CHESS2_SPRITE_H

#include <blah.h>
#include <iostream>
#include <stdarg.h>

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
    virtual void update() = 0;
    virtual void draw(Batch *batch) = 0;
};


#endif //CHESS2_SPRITE_H
