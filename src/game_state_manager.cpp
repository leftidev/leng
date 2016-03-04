#include "game_state_manager.h"
#include "input_manager.h"

namespace leng {
    
GameStateManager::GameStateManager() : running(false) {}
    
GameStateManager::~GameStateManager() {}

void GameStateManager::change_game_state(GameState* state) {
    if(!running) {
	running = true;
    }

    // cleanup the current state
    if(!game_states.empty()) {
	game_states.pop_back();
    }

    // store and init the new game state
    game_states.push_back(state);
    game_states.back()->init();
}

void GameStateManager::update(float delta_time) {
    game_states.back()->update(delta_time);
}

void GameStateManager::handle_events(InputManager& input_manager) {
    game_states.back()->handle_events(input_manager);
}

void GameStateManager::draw() {
    game_states.back()->draw();
}

} // namespace leng
