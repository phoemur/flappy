#ifndef PIPE_H
#define PIPE_H

#include "texture.h"

#include <utility>
#include <SDL.h>

class Pipe {
    Texture texture;
    std::pair<SDL_Rect,SDL_Rect> colliders;

public:
    bool left_behind = false;

    Pipe();
    explicit Pipe(int posX, int pass_height=100, int pass_size=120);

    void render();
    void set_pos(int posX) noexcept;
    void set_height(int pass_height) noexcept;
    void scroll(int distance) noexcept;

    const std::pair<SDL_Rect,SDL_Rect>& get_collider() const noexcept {return colliders;}
    int                                      get_pos() const noexcept {return colliders.first.x;}
    int                                    get_width() const noexcept {return colliders.first.w;}
};

#endif // PIPE_H
