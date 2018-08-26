#ifndef INTRO_H
#define INTRO_H

#include "gamestate.h"
#include "texture.h"
#include "background.h"
#include "font.h"
#include "mainwindow.h"

//class MainWindow; // Forward declare

class Intro : public GameState {
    MainWindow* win;
    Background background;
    Texture title;
    Texture subtitle;
    Font f1, f2;
public:
    Intro();
    Intro(const Intro&) = delete;
    Intro& operator=(const Intro&) = delete;

    void handle_events() override;
    void logic() override;
    void render() override;
};

#endif // INTRO_H
