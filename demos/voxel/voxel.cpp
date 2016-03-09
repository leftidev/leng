#include <string>
#include <iostream>

#include "window.h"
#include "input_manager.h"
#include "camera_3d.h"
#include "shader.h"
#include "resource_manager.h"
#include "renderer_voxel.h"
#include "chunk.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float SCREEN_WIDTH = 1024.0f;
float SCREEN_HEIGHT = 768.0f;

// Deltatime
float deltaTime = 0.0f;	 // Time between current frame and last frame
float lastFrame = 0.0f;  // Time of last frame

leng::Camera3D camera(glm::vec3(0.0f, 0.0f, 15*leng::BLOCK_RENDER_SIZE));

void handleEvents(leng::InputManager& inputManager) {
	if(inputManager.isPressed(SDLK_w))
	    camera.handleKeyboard(FORWARD, deltaTime);
	if(inputManager.isPressed(SDLK_s))
	    camera.handleKeyboard(BACKWARD, deltaTime);
	if(inputManager.isPressed(SDLK_a))
	    camera.handleKeyboard(LEFT, deltaTime);
	if(inputManager.isPressed(SDLK_d))
	    camera.handleKeyboard(RIGHT, deltaTime);
}

int main() {
    leng::Window window("leng++", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.setVsync(true);
    window.enableDepthTest();
    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);

    leng::RendererVoxel* renderer = new leng::RendererVoxel;
    
    leng::Chunk* chunk = new leng::Chunk;    

    GLuint sand_floor = leng::ResourceManager::getTexture("assets/textures/container.jpg").id;    

    leng::InputManager inputManager;

    float xOffset, yOffset;
    
    SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    camera.movementSpeed = 2.0f;
    
    bool running = true;
    SDL_Event event;
    while (running) {
	float currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_QUIT:
		running = false;
		break;
	    case SDL_MOUSEMOTION:
		inputManager.setMouseCoords(float(event.motion.x), float(event.motion.y));
		// FPS Camera movement
		xOffset = SCREEN_WIDTH / 2 - event.motion.x;
		yOffset = SCREEN_HEIGHT / 2 - event.motion.y;
		camera.handleMouseMovement(xOffset, yOffset);
		break;
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		inputManager.handleKeyboardEvent(event);
		break;
	    case SDL_KEYDOWN:
		inputManager.handleKeyboardEvent(event);
		break;
	    case SDL_MOUSEBUTTONUP:
		inputManager.handleMouseEvent(event);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		inputManager.handleMouseEvent(event);
		break;
	    }
	}
	handleEvents(inputManager);

	SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	// Rendering
        glClearColor(0.5f, 0.8f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sand_floor);

	chunk->render(renderer, camera);

	// Swap buffers
	window.swapWindow();
    }
    delete chunk;
    delete renderer;
    
    return 0;
}
