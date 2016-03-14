#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "leng.h"

namespace leng {
    
class InputManager {
public:
    void handleKeyboardEvent(SDL_Event event);
    void handleMouseEvent(SDL_Event event);
    bool isPressed(unsigned int key_code);
    bool isReleased(unsigned int key_code);
    void setMouseCoords(float x, float y);
    glm::vec2 getMouseCoords() { return mouseCoords; }
    glm::vec2 mouseCoords;
private:
    std::unordered_map<unsigned int, bool> keyState;
};

} // namespace leng

#endif // INPUT_MANAGER_H
