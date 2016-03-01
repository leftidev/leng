#include "window.h"
#include "game_state_manager.h"
#include "play_state.h"

int main() {
    leng::Window window("leng++ pong", 800, 600);
    window.set_vsync(true);    
    leng::sound_init();

    leng::GameStateManager state_manager;
    state_manager.change_game_state(new PlayState(state_manager, window));

    SDL_Event event;
    while (state_manager.running) {
	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { state_manager.quit(); }
		break;
	    case SDL_QUIT:
		state_manager.quit();
		break;
	    }
	    state_manager.handle_events(event);
	}

	state_manager.update();
	state_manager.draw();
    }
    
    return 0;
}
