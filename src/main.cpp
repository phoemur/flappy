#include "mainwindow.h"
#include "gamestate.h"
#include "intro.h"
#include "music.h"

#include <SDL.h>
#include <memory>

int main()
{
    // MainWindow must be the first object instanciated
    MainWindow win (640, 480, "Flappy Bird Remake");
    win.setIcon("./flappy_assets/flappy.png");

    Music mus {"./flappy_assets/Running Away - John Charles Fiddy.mp3"};
    mus.play();

    std::unique_ptr<GameState> currentState {std::make_unique<Intro>()};

    while (GameState::curr_state != GameStates::Quit) {
        currentState->handle_events();
        currentState->logic();
        currentState->render();

        changeState(currentState);
    }

    return 0;
}
