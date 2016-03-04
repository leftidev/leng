#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace leng {

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();
    void enable_depth_test();
    void swap_window();
    void set_vsync(bool flag);
    
private:
    SDL_GLContext context;
    SDL_Window* window;
};

}  // namespace leng

#endif // WINDOW_H
