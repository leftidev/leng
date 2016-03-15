#include "game_state.h"
#include "game_state_manager.h"

namespace leng {
    
    GameState::GameState(GameStateManager& StateManager, Window& Window, InputManager& InputManager) :
    stateManager(StateManager),
    window(Window),
    inputManager(InputManager) { }

GameState::~GameState() {}

void GameState::changeGameState(GameStateManager& manager, GameState* state) {
    manager.changeGameState(state);
}

} // namespace leng
