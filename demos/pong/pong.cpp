#include "window.h"
#include "shader.h"

#include <string>
#include <iostream>

int main() {
    leng::Window window("leng++", 800, 600);
    window.set_vsync(true);

    leng::Shader vertex_shader("assets/shaders/pong.vert", GL_VERTEX_SHADER);
    
    bool running = true;
    SDL_Event event;
    while (running) {
	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		break;
	    case SDL_QUIT:
		running = false;
		break;
	    }
	}
	// Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Swap buffers
	window.swap_window();
    }
    
    return 0;
}
