#include <iostream>
#include "menu_state.h"
#include "play_state.h"

MenuState::MenuState(leng::GameStateManager& state_manager, leng::Window& window) : GameState(state_manager, window) { }

MenuState::~MenuState() { }

void MenuState::load_shaders() {
    // Create and compile the shaders
    shaders.push_back(leng::Shader("assets/shaders/pong.vert", GL_VERTEX_SHADER));
    shaders.push_back(leng::Shader("assets/shaders/pong.frag", GL_FRAGMENT_SHADER));
    // Link the shaders
    shader_program.link_shaders(shaders);    
}

void MenuState::init() {
    load_shaders();

    renderer.init_vao(shader_program);

    camera.init(800, 600);
}

void MenuState::handle_events(SDL_Event event) {
    switch(event.type) {
  case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_UP) { std::cout << "Up arrow pressed" << std::endl; }
      if (event.key.keysym.sym == SDLK_DOWN) { std::cout << "Down arrow pressed" << std::endl; }
      if (event.key.keysym.sym == SDLK_RETURN) {
	  change_game_state(state_manager, new PlayState(state_manager, window));
      }
      break;
  case SDL_KEYUP:
      break;
  } 

}

void MenuState::update(float delta_time) {
    do_collisions();
    camera.update();
}

void MenuState::draw() {
    // Rendering
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader_program.program_id, "my_texture"), 0);
	
    shader_program.enable();

    // Grab the camera matrix
    glm::mat4 proj_mat = camera.get_camera_matrix();
    GLuint camera_loc = shader_program.get_uniform_location("transform");
    glUniformMatrix4fv(camera_loc, 1, GL_FALSE, glm::value_ptr(proj_mat));

    // Draw
    // ...
    
    shader_program.disable();
	
    // Swap buffers
    window.swap_window();
}

void MenuState::do_collisions() {
    
}
