#include <iostream>

#include "window.h"
#include "game_state_manager.h"
#include "play_state.h"

void pong_events(SDL_Event event, leng::Player& player) {
    switch(event.type) {
  case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_UP) { player.up_held = true; }
      if (event.key.keysym.sym == SDLK_DOWN) { player.down_held = true; }
  break;
  case SDL_KEYUP:
    if (event.key.keysym.sym == SDLK_UP) { player.up_held = false; }
    if (event.key.keysym.sym == SDLK_DOWN) { player.down_held = false; }
  break;
  } 
}

int main() {
    leng::Window window("leng++ pong", SCREEN_WIDTH, SCREEN_HEIGHT);
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
	    //pong_events(event, player);
	}
	state_manager.handle_events();
	state_manager.update();
	state_manager.draw();
    }
    
    return 0;
}
