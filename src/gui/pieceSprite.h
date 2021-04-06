#ifndef CHESS2_PIECESPRITE_H
#define CHESS2_PIECESPRITE_H

#include "sprite.h"

class PieceSprite : public Sprite {
private:
    Vec2 focus;
    bool overlapsMouse();
    bool touched;
public:
    enum State {
        IDLE, CHOOSING, MOVING, ATTACKING
    };
    State state;
    bool active;
    int id;
    int hp;
    PieceSprite(int x, int y, int id, const String& texturePath);
    void update() override;
    void draw(Batch *batch) override;
    void setFocus(Vec2 focus);
    void setCoords(int x, int y);
    int getPieceCode(int piece);
    std::vector<Vec2> getMovePositions(int data[7][11]);
    std::vector<Vec2> getAttackPositions(int data[7][11]);
};


#endif //CHESS2_PIECESPRITE_H
