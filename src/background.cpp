#include "background.h"

Background::Background(const std::string& path)
    : t{}, scrollingOffset{0}
{
    t.loadFromFile(path);
}

void Background::render()
{
    // Render 2 copies
    t.render(static_cast<int>(scrollingOffset), 0);
    t.render(static_cast<int>(scrollingOffset - t.getWidth()), 0);
}

void Background::scroll(int distance)
{
    scrollingOffset -= distance;
    if( scrollingOffset < 0 ) { scrollingOffset = t.getWidth(); }
}
