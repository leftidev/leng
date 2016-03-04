#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#include "SDL2/SDL.h"

namespace leng {
    
class InputManager {
public:
    void handle_keyboard_event(SDL_Event event);

    bool is_pressed(unsigned int key_code);
    bool is_released(unsigned int key_code);

private:
    std::unordered_map<unsigned int, bool> key_state;
};

} // namespace leng
#endif // INPUT_MANAGER_H
