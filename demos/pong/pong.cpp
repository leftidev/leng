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
#include "player.h"
#include "enemy.h"
#include "sound.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


void load_shaders(std::vector<leng::Shader>& shaders, leng::ShaderProgram& shader_program) {
    // Create and compile the shaders
    shaders.push_back(leng::Shader("assets/shaders/pong.vert", GL_VERTEX_SHADER));
    shaders.push_back(leng::Shader("assets/shaders/pong.frag", GL_FRAGMENT_SHADER));
    // Link the shaders
    shader_program.link_shaders(shaders);
}

void do_collisions(leng::Entity& player, leng::Entity& enemy, leng::Entity& ball, leng::SoundEffect& ball_hits_player, leng::SoundEffect& ball_hits_enemy, leng::SoundEffect& scoring_point) {
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

void pong_events(SDL_Event event, leng::Player& player) {
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

int main() {
    leng::Window window("leng++ pong", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.set_vsync(true);
    
    leng::sound_init();

    leng::SoundEffect ball_hits_enemy("assets/sounds/ball_hits_enemy.wav");
    leng::SoundEffect ball_hits_player("assets/sounds/ball_hits_player.wav");
    leng::SoundEffect scoring_point("assets/sounds/scoring_point.wav");
    
    std::vector<leng::Shader> shaders;
    leng::ShaderProgram shader_program;
    load_shaders(shaders, shader_program);

    leng::Renderer renderer(shader_program);

    leng::Player player(-SCREEN_WIDTH / 2, 0, 24, 128, "assets/textures/paddle_24x128.png");

    leng::Enemy enemy(SCREEN_WIDTH / 2 - 24, 0, 24, 128, "assets/textures/paddle_24x128.png");
    
    leng::Entity ball(0, 0, 24, 24, "assets/textures/ball_24x24.png");
    ball.vel.x = 5.0f;
    ball.vel.y = 5.0f;
    ball.moving = true;
    
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
	    pong_events(event, player);
	}
	camera.update();
	player.update();
	enemy.update(ball);
	ball.update();
	do_collisions(player, enemy, ball, ball_hits_player, ball_hits_enemy, scoring_point);
	
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
