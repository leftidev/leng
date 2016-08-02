#include "game_state_manager.h"
#include "input_manager.h"
#include "game_state.h"
#include <iostream>

namespace leng {
    
GameStateManager::GameStateManager() : running(false) {}
    
GameStateManager::~GameStateManager() {}

void GameStateManager::changeGameState(GameState* state) {
    if(!running) {
	running = true;
    }

    // cleanup the current state
    if(!gameStates.empty()) {
	for(unsigned int i = 0; i < gameStates.size(); i++) {
	    delete gameStates[i];
	}
        gameStates.clear();
	
	std::cout << "Cleaning up GameState" << std::endl;
	//
    }

    // store and init the new game state
    gameStates.push_back(state);
}

void GameStateManager::update(float deltaTime) {
    if(!gameStates.empty()) {
	gameStates.back()->update(deltaTime);
    }
}

void GameStateManager::handleEvents(InputManager* inputManager, float deltaTime) {
    if(!gameStates.empty()) {
	gameStates.back()->handleEvents(inputManager, deltaTime);
    }
}

void GameStateManager::draw() {
    if(!gameStates.empty()) {
	gameStates.back()->draw();
    }
}

} // namespace leng
