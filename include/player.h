#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"

class Player {
    Texture texture;

public:
    bool isDead;
    double posX, posY;
    double radius;
    double vertSpeed, vertAccel;

    Player(double x, double y);

    void make_jump();
    void render();
    void apply_forces();
};

#endif // PLAYER_H
