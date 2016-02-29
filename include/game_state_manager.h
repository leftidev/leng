#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include <vector>
#include "game_state.h"

namespace leng {
    
class GameStateManager {
public:
    GameStateManager();
    ~GameStateManager();

    void change_game_state(GameState* state);
    void update();
    void handle_events();
    void draw();
    void quit() { running = false; }

    std::vector<GameState*> game_states;
    bool running;
};

}

#endif // GAME_STATE_MANAGER_H
