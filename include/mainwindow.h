#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <SDL.h>

class MainWindow final {
    int width;
    int height;
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
public:
    MainWindow(int w, int h, const std::string& title = " ");
    ~MainWindow() noexcept;
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

    void setIcon(const std::string& path);
    void clear();
    void update();

    SDL_Renderer* getRenderer() const noexcept {return gRenderer;}
    SDL_Window*     getWindow() const noexcept {return gWindow;  }
    int              getWidth() const noexcept {return width;    }
    int             getHeight() const noexcept {return height;   }
};

#endif // MAINWINDOW_H
