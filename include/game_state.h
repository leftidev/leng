#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "SDL2/SDL.h"

#include "window.h"
#include "input_manager.h"

namespace leng {

class GameStateManager;

class GameState {
public:
    GameState(GameStateManager* StateManager, Window* Window, InputManager* InputManager);
    ~GameState();

    virtual void init() = 0;
    virtual void handleEvents(InputManager* input_manager, float deltaTime) = 0;
    virtual void update(float delta_time) = 0;
    virtual void draw() = 0;
    void changeGameState(GameStateManager* manager, GameState* state);

    GameStateManager* stateManager;
    Window* window;
    InputManager* inputManager;
};

} // namespace leng

#endif // GAME_STATE_H
