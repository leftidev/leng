#ifndef MENU_STATE_H
#define MENU_STATE_H


#include "game_state.h"
#include "window.h"
#include "shader.h"
#include "shader_program.h"
#include "sound.h"
#include "renderer.h"
#include "sprite.h"
#include "camera_2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class MenuState : public leng::GameState {
public:
    MenuState(leng::GameStateManager& state_manager, leng::Window& window);
    ~MenuState();

    void init() override;
    void handle_events(SDL_Event event) override;
    void update(float delta_time) override;
    void draw() override;
    void load_shaders();
    void do_collisions();
    
private:
    std::vector<leng::Shader> shaders;
    leng::ShaderProgram shader_program;
    leng::Renderer renderer;
    leng::Camera2D camera;
};

#endif // MENU_STATE_H
