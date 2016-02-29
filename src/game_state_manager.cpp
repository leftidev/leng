#include "game_state_manager.h"

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

void GameStateManager::update() {
    game_states.back()->update();
}

void GameStateManager::handle_events() {
    game_states.back()->handle_events();
}

void GameStateManager::draw() {
    game_states.back()->draw();
}

} // namespace leng
