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
    Sprite() = default; // Para evitar instanciar la clase
public:
    TextureRef texture;

    int getX();
    int getY();
    void setX(int);
    void setY(int);

    virtual void update() = 0;
    virtual void draw(Batch *batch);
};


#endif //CHESS2_SPRITE_H
