#ifndef CHESS2_SPRITE_H
#define CHESS2_SPRITE_H

#include <blah.h>
#include <iostream>

using namespace Blah;

class Sprite {
private:
    int x, y;
    friend std::ostream& operator<<(std::ostream &strm, const Sprite &sprite);

public:
    void load(int x, int y, const String& texturePath);
    TextureRef texture;
    int getX();
    void setX(int);
    int getY();
    void setY(int);
    void draw(Batch *batch);

    Sprite() = default;
};


#endif //CHESS2_SPRITE_H
