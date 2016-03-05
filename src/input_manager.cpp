#include "input_manager.h"

#include <iostream>

namespace leng {
    
void InputManager::handle_keyboard_event(SDL_Event event) {
    key_state[event.key.keysym.sym] = event.key.state;
}

void InputManager::handle_mouse_event(SDL_Event event) {
    key_state[event.button.button] = event.button.state;
}

bool InputManager::is_pressed(unsigned int key_code) {
    return (key_state[key_code] == SDL_PRESSED);
}
bool InputManager::is_released(unsigned int key_code) {
    return (key_state[key_code] == SDL_RELEASED);
}

void InputManager::set_mouse_coords(float x, float y) {
    mouse_coords.x = x;
    mouse_coords.y = y;
}

} // namespace leng
