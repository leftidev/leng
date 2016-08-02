#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <vector>
#include <memory>

namespace leng {

class InputManager;
class GameState;

class GameStateManager {
public:
    GameStateManager();
    ~GameStateManager();

    void changeGameState(GameState* state);
    void update(float deltaTime);
    void handleEvents(InputManager* inputManager, float deltaTime);
    void draw();
    void quit() { running = false; }

    std::vector<GameState*> gameStates;
    bool running;
};

}

#endif // GAME_STATE_MANAGER_H
