#include <string>
#include <iostream>
#include <vector>

#include "window.h"
#include "shader.h"
#include "shader_program.h"
#include "camera_2d.h"
#include "renderer.h"
#include "collision.h"
#include "entity.h"
#include "sprite.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Key inputs
bool up_held = false;
bool down_held = false;

void load_shaders(std::vector<leng::Shader>& shaders, leng::ShaderProgram& shader_program) {
    // Create and compile the shaders
    shaders.push_back(leng::Shader("assets/shaders/pong.vert", GL_VERTEX_SHADER));
    shaders.push_back(leng::Shader("assets/shaders/pong.frag", GL_FRAGMENT_SHADER));
    // Link the shaders
    shader_program.link_shaders(shaders);
}

void do_collisions(leng::Entity player, leng::Entity enemy, leng::Entity ball) {
    if(do_boxes_intersect(player.aabb, ball.aabb)) {
	ball.vel.x *= -1;
    }
    if(do_boxes_intersect(enemy.aabb, ball.aabb)) {
	ball.vel.x *= -1;
    }
    if(ball.pos.x < -SCREEN_WIDTH / 2 || ball.pos.x > SCREEN_WIDTH / 2 - 24) {
	ball.vel.x *= -1;
    }
    if(ball.pos.y < -SCREEN_HEIGHT / 2 || ball.pos.y > SCREEN_HEIGHT / 2 - 24) {
	ball.vel.y *= -1;
    }
}

void enemy_update(leng::Entity enemy) {
    
}

void player_update(leng::Entity player) {
    if(up_held) {
	player.pos.y += player.vel.y;
	std::cout << "woop" << std::endl;
    }
    if(down_held) {
	player.pos.y -= player.vel.y;
    }
}

void ball_update(leng::Entity ball) {
    
}

void pong_events(SDL_Event event) {
    switch(event.type) {
  case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_UP) { up_held = true; }
      if (event.key.keysym.sym == SDLK_DOWN) { down_held = true; }
  break;
  case SDL_KEYUP:
    if (event.key.keysym.sym == SDLK_UP) { up_held = false; }
    if (event.key.keysym.sym == SDLK_DOWN) { down_held = false; }
  break;
  }
    
}

int main() {
    leng::Window window("leng++ pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.set_vsync(true);

    std::vector<leng::Shader> shaders;
    leng::ShaderProgram shader_program;
    load_shaders(shaders, shader_program);

    leng::Renderer renderer(shader_program);

    leng::Entity player(-SCREEN_WIDTH / 2, 0, 24, 128, "assets/textures/paddle_24x128.png");
    player.vel.x = 5.0f;
    player.vel.y = 5.0f;

    leng::Entity enemy(SCREEN_WIDTH / 2 - 24, 0, 24, 128, "assets/textures/paddle_24x128.png");
    enemy.vel.x = 5.0f;
    enemy.vel.y = 5.0f;
    
    leng::Entity ball(0, 0, 24, 24, "assets/textures/ball_24x24.png");

    leng::Sprite mid_line(-5, -SCREEN_HEIGHT / 2, 10, 1024, "assets/textures/midline_10x1024.png");
    
    // Set up the camera
    leng::Camera2D camera;
    camera.init(800, 600);
    
    bool running = true;
    SDL_Event event;
    while (running) {
	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		break;
	    case SDL_QUIT:
		running = false;
		break;
	    }
	    pong_events(event);
	}
	camera.update();
	player.update();
	player_update(player);
	//enemy.update();
	ball.update();
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
    
    return 0;
}
