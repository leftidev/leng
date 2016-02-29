#include "game_state.h"
#include "game_state_manager.h"

namespace leng {
    
    GameState::GameState(GameStateManager& _state_manager, Window& _window) :
	state_manager(_state_manager),
	window(_window) { }

GameState::~GameState() {}

    void GameState::change_game_state(GameStateManager& manager, GameState* state) {
	manager.change_game_state(state);
    }

} // namespace leng
