#ifndef LEVEL_H
#define LEVEL_H

#include "gamestate.h"
#include "background.h"
#include "player.h"
#include "music.h"
#include "pipe.h"
#include "texture.h"
#include "font.h"

#include <array>
#include <random>

class MainWindow; // forward declare

class Level : public GameState {
    MainWindow* win;
    Background background;
    Player pl;
    Sound jump_s;
    Sound lost_s;
    std::array<Pipe, 3> pipes;
    Font font;
    Texture title;

    std::random_device seeder {};
    std::mt19937 engine;
    std::uniform_int_distribution<int> dist;

public:
    Level();
    Level(const Level&) = delete;
    Level& operator=(const Level&) = delete;

    void handle_events() override;
    void logic() override;
    void render() override;

private:
    inline bool hit_bottom() noexcept;
    inline bool hit_roof() noexcept;
    inline void check_bounds();
    inline void check_all_collisions();
    inline void check_score();
};

bool check_collision(const Player& pl, const Pipe& pip) noexcept;
bool check_collision(const Player& pl, const SDL_Rect& rec) noexcept;

#endif // LEVEL_H
