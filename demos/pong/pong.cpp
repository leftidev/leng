#include "window.h"
#include "game_state_manager.h"
#include "input_manager.h"
#include "menu_state.h"
#include "play_state.h"

int main() {
    leng::Window window("leng++ pong", 800, 600);
    window.set_vsync(true);    
    leng::sound_init();

    leng::GameStateManager state_manager;
    state_manager.change_game_state(new PlayState(state_manager, window));

    leng::InputManager input_manager;

    int physics_steps = 2;

    float delta_time = 0.0f; // Time between current frame and last frame
    float last_frame = 0.0f; // Time of last frame
    
    SDL_Event event;
    while (state_manager.running) {
	float current_frame = SDL_GetTicks();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { state_manager.quit(); }
		input_manager.handle_keyboard_event(event);
		break;
	    case SDL_KEYDOWN:
		input_manager.handle_keyboard_event(event);
		break;
	    case SDL_QUIT:
		state_manager.quit();
		break;
	    }
	}
	state_manager.handle_events(input_manager);

	for (int i = 0; i < physics_steps; i++) {
	    // Update logic
	    state_manager.update(delta_time / physics_steps);
	}

	state_manager.draw();
    }
    
    return 0;
}
