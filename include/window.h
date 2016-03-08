#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace leng {

class Window {
public:
    Window(std::string title, int width, int height);
    ~Window();
    void enableDepthTest();
    void swapWindow();
    void setVsync(bool flag);
    
    SDL_Window* window;
    
private:
    SDL_GLContext context;
};

}  // namespace leng

#endif // WINDOW_H
