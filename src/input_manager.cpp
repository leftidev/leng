#include "input_manager.h"

namespace leng {
    
void InputManager::handle_keyboard_event(SDL_Event event) {
    key_state[event.key.keysym.sym] = event.key.state;
}

bool InputManager::is_pressed(unsigned int key_code) {
    return (key_state[key_code] == SDL_PRESSED);
}
bool InputManager::is_released(unsigned int key_code) {
    return (key_state[key_code] == SDL_RELEASED);
}

} // namespace leng
