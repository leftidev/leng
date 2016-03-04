#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SDL2/SDL.h"

namespace leng {
    
class InputManager {
public:
    void handle_keyboard_event(SDL_Event event);

    bool is_pressed(unsigned int key_code);
    bool is_released(unsigned int key_code);

private:
    bool key_state[1024] {SDL_RELEASED};
};

} // namespace leng
#endif // INPUT_MANAGER_H
