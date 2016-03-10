#include "window.h"
#include "game_state_manager.h"
#include "input_manager.h"
#include "play_state.h"

int main() {
    leng::Window window("leng++ pong", 800, 600);
    window.setVsync(true);    
    //leng::soundInit();

    leng::GameStateManager stateManager;
    stateManager.changeGameState(new PlayState(stateManager, window));

    leng::InputManager inputManager;

    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    
    SDL_Event event;
    while (stateManager.running) {
	float currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { stateManager.quit(); }
		inputManager.handleKeyboardEvent(event);
		break;
	    case SDL_KEYDOWN:
		inputManager.handleKeyboardEvent(event);
		break;
	    case SDL_QUIT:
		stateManager.quit();
		break;
	    }
	}
	stateManager.handleEvents(inputManager);

	// Update logic
	stateManager.update(deltaTime);

	stateManager.draw();
    }
    
    return 0;
}
