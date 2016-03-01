#include "play_state.h"

PlayState::PlayState(leng::GameStateManager& state_manager, leng::Window& window) : GameState(state_manager, window) { }

PlayState::~PlayState() { }

void PlayState::load_shaders() {
    // Create and compile the shaders
    shaders.push_back(leng::Shader("assets/shaders/pong.vert", GL_VERTEX_SHADER));
    shaders.push_back(leng::Shader("assets/shaders/pong.frag", GL_FRAGMENT_SHADER));
    // Link the shaders
    shader_program.link_shaders(shaders);    
}

void PlayState::init() {
    load_shaders();

    renderer.init_vao(shader_program);

    camera.init(800, 600);
    
    ball.vel.x = 5.0f;
    ball.vel.y = 5.0f;
    ball.moving = true;    
}

void PlayState::handle_events(SDL_Event event) {
    switch(event.type) {
  case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_UP) { player.up_held = true; }
      if (event.key.keysym.sym == SDLK_DOWN) { player.down_held = true; }
  break;
  case SDL_KEYUP:
    if (event.key.keysym.sym == SDLK_UP) { player.up_held = false; }
    if (event.key.keysym.sym == SDLK_DOWN) { player.down_held = false; }
  break;
  } 

}

void PlayState::update() {
    do_collisions();
    camera.update();
    player.update();
    enemy.update(ball);
    ball.update();
}

void PlayState::draw() {
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

    renderer.draw(mid_line);
    renderer.draw(player.sprite);
    renderer.draw(enemy.sprite);
    renderer.draw(ball.sprite);

    shader_program.disable();
	
    // Swap buffers
    window.swap_window();
}

void PlayState::do_collisions() {
    if(do_boxes_intersect(player.aabb, ball.aabb)) {
	ball_hits_player.play();
	ball.vel.x *= -1;
    }
    if(do_boxes_intersect(enemy.aabb, ball.aabb)) {
	ball_hits_enemy.play();
	ball.vel.x *= -1;
    }
    // Ball hits goal
    if(ball.pos.x < -SCREEN_WIDTH / 2 || ball.pos.x > SCREEN_WIDTH / 2 - 24) {
	scoring_point.play();
	ball.pos.x = 0;
	ball.pos.y = 0;
    }
    // Ball hits top or bot border
    if(ball.pos.y < -SCREEN_HEIGHT / 2 || ball.pos.y > SCREEN_HEIGHT / 2 - 24) {
	ball.vel.y *= -1;
    }
}
