#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <unordered_map>

#include "SDL2/SDL.h"

#include "leng.h"

namespace leng {
    
class InputManager {
public:
    void handle_keyboard_event(SDL_Event event);
    void handle_mouse_event(SDL_Event event);
    bool is_pressed(unsigned int key_code);
    bool is_released(unsigned int key_code);
    void set_mouse_coords(SDL_Event event);

    Position mouse_coords;
private:
    std::unordered_map<unsigned int, bool> key_state;
};

} // namespace leng
#endif // INPUT_MANAGER_H
