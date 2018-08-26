#include "intro.h"
#include "mainwindow.h"
#include "locator.hpp"

Intro::Intro()
    : win{Locator<MainWindow>::get()}, background{"./flappy_assets/clouds.jpg"}, title{}, subtitle{}, f1{}, f2{}
{
    f1.loadFromFile("./flappy_assets/Purisa-BoldOblique.ttf", 30);
    f2.loadFromFile("./flappy_assets/Purisa-BoldOblique.ttf", 16);
    title.loadFromRenderedText("Flappy Bird remake", f1, SDL_Color{0xFF,0,0,0xFF});
    subtitle.loadFromRenderedText("Press to continue...", f2, SDL_Color{0,0,0,0xFF});
}

void Intro::handle_events()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            GameState::next_state = GameStates::Quit;
        }
        else if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_FINGERDOWN) {
            GameState::next_state = GameStates::Level;
        }
    }
}

void Intro::logic()
{
    background.scroll(3);
}

void Intro::render()
{
    win->clear();
    background.render();

    title.render(static_cast<int>((win->getWidth() - title.getWidth()) / 2),
                 static_cast<int>((win->getHeight() - title.getHeight()) / 2));
    subtitle.render(static_cast<int>((win->getWidth() - subtitle.getWidth()) / 2),
                    static_cast<int>((win->getHeight() + title.getHeight() - subtitle.getHeight()) / 2 ));
    win->update();
}
