#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "window.h"

namespace leng {
class GameStateManager;
    
class GameState {
public:
    GameState(leng::GameStateManager& _state_manager, Window& _window);
    ~GameState();

    virtual void init() = 0;
    virtual void handle_events() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    void change_game_state(GameStateManager& manager, GameState* state);

private:
    GameStateManager& state_manager;
    Window& window;
};

} // namespace leng

#endif // GAME_STATE_H
