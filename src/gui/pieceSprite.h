#ifndef CHESS2_PIECESPRITE_H
#define CHESS2_PIECESPRITE_H

#include "sprite.h"
extern "C"{
    #include "../game/game.h"
}

class PieceSprite : public Sprite {
private:
    Vec2 focus;
    bool overlapsPoint(int x, int y);
    bool overlapsMouse();
    bool mouseOverlapsPoint(int x, int y);
    bool touched;
    int dmg;
public:
    enum State {
        IDLE, CHOOSING, MOVING, ATTACKING
    };
    State state;
    bool active;
    int id, hp;
    PieceSprite(int x, int y, int id, const String& texturePath);
    void update(Game *game);
    void draw(Batch *batch) override;
    int getDmg();
    int getPieceCode();
    std::vector<Vec2> getMovePositions(int data[7][11]);
    std::vector<Vec2> getAttackPositions(int data[7][11]);
};


#endif //CHESS2_PIECESPRITE_H
