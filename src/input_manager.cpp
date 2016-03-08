#include <iostream>

#include "input_manager.h"

namespace leng {
    
void InputManager::handleKeyboardEvent(SDL_Event event) {
    keyState[event.key.keysym.sym] = event.key.state;
}

void InputManager::handleMouseEvent(SDL_Event event) {
    keyState[event.button.button] = event.button.state;
}

bool InputManager::isPressed(unsigned int key_code) {
    return (keyState[key_code] == SDL_PRESSED);
}
bool InputManager::isReleased(unsigned int key_code) {
    return (keyState[key_code] == SDL_RELEASED);
}

void InputManager::setMouseCoords(float x, float y) {
    mouseCoords.x = x;
    mouseCoords.y = y;
}

} // namespace leng
