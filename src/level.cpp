#include "level.h"
#include "mainwindow.h"
#include "locator.hpp"

#include <cmath>
#include <string>

Level::Level()
    : win{Locator<MainWindow>::get()},
      background{"./flappy_assets/clouds.jpg"},
      pl{win->getWidth() / 4.0, win->getHeight() / 2.0},
      jump_s{"./flappy_assets/jump.wav"},
      lost_s{"./flappy_assets/lost.wav"},
      pipes{},
      font{},
      title{},
      engine{this->seeder()},
      dist{30, 310}

{
    GameState::score = 0;

    font.loadFromFile("./flappy_assets/Purisa-BoldOblique.ttf", 30);

    for (decltype(pipes)::size_type i=0; i<pipes.size(); ++i) {
        pipes[i].set_pos(win->getWidth() + i * (win->getWidth() + pipes[i].get_width()) / pipes.size());
        pipes[i].set_height(dist(engine));
    }
}

void Level::handle_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            GameState::next_state = GameStates::Quit;
        }
        else if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_FINGERDOWN) {
            if (!pl.isDead) {
                pl.make_jump();
                jump_s.play();
            }
        }
    }
}


void Level::logic()
{
    // Apply changes to the player
    pl.apply_forces();

    // Check collisions
    check_bounds();
    if (!pl.isDead) check_all_collisions();

    // Check score
    check_score();

    // Move forward
    background.scroll(3);
    for (auto& pip: pipes) {
        pip.scroll(3);
        if (pip.get_pos() < 0 - pip.get_width()) {
            // Update position and height
            pip.set_pos(win->getWidth());
            pip.set_height(dist(engine));
            pip.left_behind = false;
        }
    }
}

void Level::render()
{
    win->clear();

    background.render();
    for (auto& pip: pipes) pip.render();

    title.loadFromRenderedText("Score: " + std::to_string(GameState::score), font, SDL_Color{0xFF,0,0,0xFF});
    title.render(static_cast<int>((win->getWidth() - title.getWidth()) / 2),
                 static_cast<int>(title.getHeight() / 2));

    pl.render();

    win->update();
}

bool Level::hit_bottom() noexcept
{
    return pl.posY + pl.radius > win->getHeight();
}

bool Level::hit_roof() noexcept
{
    return pl.posY <= pl.radius;
}

void Level::check_bounds()
{
    if (!pl.isDead && hit_roof()) {
        pl.isDead = true;
        lost_s.play();
    }
    else if (hit_bottom()) {
        GameState::next_state = GameStates::Lost;
        if (!pl.isDead) {lost_s.play();}
    }
}

void Level::check_all_collisions()
{
    for (auto& pip: pipes) {
        if (check_collision(pl, pip)) {
            pl.isDead = true;
            lost_s.play();
            break;
        }
    }
}

void Level::check_score()
{
    if (!pl.isDead) {
        for (auto& pip: pipes) {
            if (!pip.left_behind) {
                if (std::abs(pl.posX - (pip.get_pos() + pip.get_width())) < pl.radius) {
                    ++GameState::score;
                    pip.left_behind = true;
                    break;
                }
            }
        }
    }
}

bool check_collision(const Player& pl, const Pipe& pip) noexcept
{
    auto& collider = pip.get_collider();
    return check_collision(pl, collider.first) || check_collision(pl, collider.second);
}

bool check_collision(const Player& pl, const SDL_Rect& rec) noexcept
{
    //Closest point on collision box
    int cX, cY;

    //Closest x offset
    if(pl.posX < rec.x) {
        cX = rec.x;
    }
    else if( pl.posX > rec.x + rec.w ) {
        cX = rec.x + rec.w;
    }
    else {
        cX = static_cast<int>(pl.posX);
    }

    //Closest y offset
    if(pl.posY < rec.y ) {
        cY = rec.y;
    }
    else if(pl.posY > rec.y + rec.h) {
        cY = rec.y + rec.h;
    }
    else {
        cY = static_cast<int>(pl.posY);
    }

    //If the closest point is inside the circle
    if(std::hypot(cX - pl.posX, cY - pl.posY) < pl.radius) {
        return true;
    }
    else return false;
}
