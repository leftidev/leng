#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "SDL2/SDL_ttf.h"

namespace leng {

class Window {
public:
    Window(std::string title, int Width, int Height);
    ~Window();
    void enableDepthTest();
    void swapWindow();
    void setVsync(bool flag);
    
    SDL_Window* window;

    int width;
    int height;
private:
    SDL_GLContext context;
};

}  // namespace leng

#endif // WINDOW_H
