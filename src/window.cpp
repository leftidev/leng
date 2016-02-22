#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "window.h"

void error(std::string message, std::string error) {
    std::cout << message + error  << std::endl;
}

namespace leng {
    
Window::Window(const char* title, int width, int height) {
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
	error("Could not initialize SDL: ", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(title,
					  100, 100,
					  width, height,
					  SDL_WINDOW_OPENGL);
    // Error checking
    if(window == nullptr) {
	error("Could not create window: ", SDL_GetError());
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    // Error checking
    if(context == nullptr) {
	error("Could not create GL context: ", SDL_GetError());
    }

    GLenum err = glewInit();

    // Error checking
    if(GLEW_OK != err) {
	std::cout << "GLEW initialization error: " << glewGetErrorString(err) << std::endl;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    
    glEnable(GL_DEPTH_TEST);
    
    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
}

Window::~Window() {}    

} // namespace leng
