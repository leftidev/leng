#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>

#include "game_state.h"
#include "window.h"
#include "shader.h"
#include "shader_program.h"
#include "sound.h"
#include "collision.h"
#include "renderer.h"
#include "sprite.h"
#include "camera_2d.h"
#include "player.h"
#include "enemy.h"
#include "entity.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class PlayState : public leng::GameState {
public:
    PlayState(leng::GameStateManager& state_manager, leng::Window& window);
    ~PlayState();

    void init() override;
    void handle_events() override;
    void update() override;
    void draw() override;
    void load_shaders();
    void do_collisions();
    
private:
    std::vector<leng::Shader> shaders;
    leng::ShaderProgram shader_program;
    leng::SoundEffect ball_hits_enemy{"assets/sounds/ball_hits_enemy.wav"};
    leng::SoundEffect ball_hits_player{"assets/sounds/ball_hits_player.wav"};
    leng::SoundEffect scoring_point{"assets/sounds/scoring_point.wav"};
    leng::Player player{-SCREEN_WIDTH / 2, 0, 24, 128, "assets/textures/paddle_24x128.png"};
    leng::Enemy enemy{SCREEN_WIDTH / 2 - 24, 0, 24, 128, "assets/textures/paddle_24x128.png"};
    leng::Entity ball{0, 0, 24, 24, "assets/textures/ball_24x24.png"};
    leng::Sprite mid_line{-5, -SCREEN_HEIGHT / 2, 10, 1024, "assets/textures/midline_10x1024.png"};
    leng::Renderer renderer;
    leng::Camera2D camera;
};

#endif // PLAY_STATE_H
