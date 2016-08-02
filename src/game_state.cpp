#include "game_state.h"

namespace leng {
    
GameState::GameState(GameStateManager* StateManager, Window* Window, InputManager* InputManager) : stateManager(StateManager), window(Window), inputManager(InputManager) { }

} // namespace leng
