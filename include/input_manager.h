#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "leng.h"

namespace leng {
    
class InputManager {
public:
    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);
    void update();
    // Returns true if the key is held down.
    bool isKeyDown(unsigned int keyID);

    // Returns true if the key was held down.
    bool wasKeyDown(unsigned int keyID);

    // Returns true if the key was just pressed.
    bool isKeyPressed(unsigned int keyID);
    void setMouseCoords(float x, float y);
    glm::vec2 getMouseCoords() { return mouseCoords; }
    glm::vec2 mouseCoords;
private:
    std::unordered_map<unsigned int, bool> keyState;
    std::unordered_map<unsigned int, bool> prevKeyState;
};

} // namespace leng

#endif // INPUT_MANAGER_H
