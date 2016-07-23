#include <iostream>


#include "window.h"

namespace leng {
    
Window::Window(std::string title, int Width, int Height) {
    width = Width;
    height = Height;
    
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
	std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    }
    const char* Title = title.c_str();
    window = SDL_CreateWindow(Title,
			      400, 300,
			      width, height,
			      SDL_WINDOW_OPENGL);
    // Error checking
    if(window == nullptr) {
	std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    }

    context = SDL_GL_CreateContext(window);

    // Error checking
    if(context == nullptr) {
	std::cout << "Could not create GL context: " << SDL_GetError() << std::endl;
    }

    GLenum err = glewInit();

    // Error checking
    if(GLEW_OK != err) {
	std::cout << "GLEW initialization error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize SDL_ttf
    if(TTF_Init() == -1) {
	printf("TTF_Init error: %s\n", TTF_GetError());
    }

}

Window::~Window() {
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}    

void Window::enableDepthTest() {
    glEnable(GL_DEPTH_TEST);
}
    
void Window::swapWindow() {
    SDL_GL_SwapWindow(window);
}

void Window::setVsync(bool flag) {
    SDL_GL_SetSwapInterval(flag);
}
    
} // namespace leng
