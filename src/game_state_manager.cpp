#include "game_state_manager.h"
#include "input_manager.h"

namespace leng {
    
GameStateManager::GameStateManager() : running(false) {}
    
GameStateManager::~GameStateManager() {}

void GameStateManager::changeGameState(GameState* state) {
    if(!running) {
	running = true;
    }

    // cleanup the current state
    if(!gameStates.empty()) {
	gameStates.pop_back();
    }

    // store and init the new game state
    gameStates.push_back(state);
    gameStates.back()->init();
}

void GameStateManager::update(float deltaTime) {
    gameStates.back()->update(deltaTime);
}

void GameStateManager::handleEvents(InputManager* inputManager, float deltaTime) {
	gameStates.back()->handleEvents(inputManager, deltaTime);
}

void GameStateManager::draw() {
    gameStates.back()->draw();
}

} // namespace leng
