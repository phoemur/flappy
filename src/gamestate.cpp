#include "gamestate.h"
#include "texture.h"
#include "font.h"
#include "locator.hpp"
#include "mainwindow.h"
#include "intro.h"
#include "level.h"

#include <SDL.h>
#include <string>

GameStates GameState::curr_state = GameStates::Intro;
GameStates GameState::next_state = GameStates::Null;
int GameState::score = 0;

GameState::~GameState() noexcept = default;

void lost()
{
    auto* win = Locator<MainWindow>::get();
    Texture back, t;
    back.loadFromFile("flappy_assets/background.jpg");
    Font f;
    f.loadFromFile("./flappy_assets/Purisa-BoldOblique.ttf", 30);
    t.loadFromRenderedText("YOU LOST!!! Score: " + std::to_string(GameState::score), f,SDL_Color{0xFF,0,0,0xFF});

    win->clear();
    back.render(0,0);
    t.render(static_cast<int>((win->getWidth() - t.getWidth()) / 2),
             static_cast<int>((win->getHeight() - t.getHeight()) / 2));
    win->update();

    SDL_Delay(2000);
}

void changeState(std::unique_ptr<GameState>& state)
{
    if (GameState::next_state != GameStates::Null) {
        switch (GameState::next_state) {
            case GameStates::Intro:
                state.reset(nullptr);
                state = std::make_unique<Intro>();
                break;
            case GameStates::Lost:
                lost();
                GameState::next_state = GameStates::Intro;
                state.reset(nullptr);
                state = std::make_unique<Intro>();
                break;
            case GameStates::Level:
                state.reset(nullptr);
                state = std::make_unique<Level>();
                break;
            default:
                break;
        }

        GameState::curr_state = GameState::next_state;
        GameState::next_state = GameStates::Null;
    }
}
