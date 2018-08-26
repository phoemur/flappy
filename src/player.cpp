#include "player.h"

#include "SDL.h"

Player::Player(double x, double y)
    : texture{}, isDead{false}, posX{x}, posY{y}, radius{0.0}, vertSpeed{0.0}, vertAccel{0.3}
{
    texture.loadFromFile("./flappy_assets/flappy.png");
    radius = texture.getWidth() / 2;
}

void Player::make_jump()
{
    if (vertSpeed > 0) vertSpeed = -5.0;
    else vertSpeed -= 5.0;
}

void Player::apply_forces()
{
    vertSpeed += vertAccel;
    posY += vertSpeed;
}



void Player::render()
{
    double angle = vertSpeed * 5.0;
    if (angle > 80.0) angle = 80.0;

    texture.render(static_cast<int>(posX - radius), static_cast<int>(posY - radius), nullptr, angle);
}
