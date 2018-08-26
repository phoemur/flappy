#include "pipe.h"

Pipe::Pipe()
    : Pipe(240)
{

}

Pipe::Pipe(int posX, int pass_height, int pass_size)
    : texture{}, colliders()
{
    texture.loadFromFile("./flappy_assets/pipe.png");

    colliders.first.x = colliders.second.x = posX;
    colliders.first.y = 0 - pass_height;
    colliders.second.y = colliders.first.y + static_cast<int>(texture.getHeight()) + pass_size;

    colliders.first.w = colliders.second.w = static_cast<int>(texture.getWidth());
    colliders.first.h = colliders.second.h = static_cast<int>(texture.getHeight());
}

void Pipe::render()
{
    texture.render(colliders.first.x,  colliders.first.y, nullptr, 0.0, nullptr, SDL_FLIP_VERTICAL); // Top pipe
    texture.render(colliders.second.x, colliders.second.y); // Bottom pipe
}

void Pipe::set_pos(int posX) noexcept
{
    colliders.first.x = colliders.second.x = posX;
}

void Pipe::set_height(int pass_height) noexcept
{
    int sz = colliders.second.y - colliders.first.y - colliders.first.h; // size of the passage
    colliders.first.y = 0 - pass_height;
    colliders.second.y = colliders.first.y + colliders.first.h + sz;
}

void Pipe::scroll(int distance) noexcept
{
    colliders.first.x -= distance;
    colliders.second.x -= distance;
}
