#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "window.h"
#include "SDL2/SDL.h"

namespace leng {

class GameStateManager;
    
class GameState {
public:
    GameState(GameStateManager& _state_manager, Window& _window);
    ~GameState();

    virtual void init() = 0;
    virtual void handle_events(SDL_Event event) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    void change_game_state(GameStateManager& manager, GameState* state);

    GameStateManager& state_manager;
    Window& window;
};

} // namespace leng

#endif // GAME_STATE_H