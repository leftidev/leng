#include "window.h"
#include "game_state_manager.h"
#include "input_manager.h"
#include "play_state.h"
#include "shader.h"
#include "sound.h"

int main() {
    leng::Window window("leng++ gravity gizmo", 1680, 1050);
    window.setVsync(true);
    leng::soundInit();

    leng::InputManager inputManager;
	
    leng::Shader shader{"assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag"};

    leng::GameStateManager stateManager;
    stateManager.changeGameState(new PlayState(&stateManager, &window, &inputManager, &shader, 2));
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frames
    
    SDL_Event event;
    while (stateManager.running) {
	float currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
	
	inputManager.update();
	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_QUIT:
		stateManager.running = false;
		break;
	    case SDL_MOUSEMOTION:
		inputManager.setMouseCoords(float(event.motion.x), float(event.motion.y));
		break;
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { stateManager.running = false; }
		inputManager.releaseKey(event.key.keysym.sym);
		break;
	    case SDL_KEYDOWN:
		inputManager.pressKey(event.key.keysym.sym);
		break;
	    case SDL_MOUSEBUTTONUP:
		inputManager.releaseKey(event.button.button);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		inputManager.pressKey(event.button.button);
		break;
	    }
	}
	stateManager.handleEvents(&inputManager, deltaTime);
	
	// Update logic
	stateManager.update(deltaTime);

	stateManager.draw();
    }
    
    return 0;
}
