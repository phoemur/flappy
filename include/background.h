#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "texture.h"

#include <string>

class Background {
    Texture t;
    double scrollingOffset;
public:
    Background(const std::string& path);

    void render();
    void scroll(int distance);
};

#endif // BACKGROUND_H
