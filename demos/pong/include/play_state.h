#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>

#include "game_state.h"
#include "window.h"
#include "shader.h"
#include "sound.h"
#include "collision.h"
#include "renderer_2d.h"
#include "sprite.h"
#include "camera_2d.h"
#include "player.h"
#include "enemy.h"
#include "entity.h"
#include "input_manager.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class PlayState : public leng::GameState {
public:
    PlayState(leng::GameStateManager& stateManager, leng::Window& window);
    ~PlayState();

    void init() override;
    void handleEvents(leng::InputManager& inputManager) override;
    void update(float deltaTime) override;
    void draw() override;
    void doCollisions();
    
private:
    leng::Shader shader{"assets/shaders/pong.vert", "assets/shaders/pong.frag"};
    leng::SoundEffect ballHitsEnemy{"assets/sounds/ball_hits_enemy.wav"};
    leng::SoundEffect ballHitsPlayer{"assets/sounds/ball_hits_player.wav"};
    leng::SoundEffect scoringPoint{"assets/sounds/scoring_point.wav"};
    leng::Player player{-SCREEN_WIDTH / 2, 0, 24, 128, "assets/textures/paddle_24x128.png"};
    leng::Enemy enemy{SCREEN_WIDTH / 2 - 24, 0, 24, 128, "assets/textures/paddle_24x128.png"};
    leng::Entity ball{0, 0, 24, 24, "assets/textures/ball_24x24.png"};
    leng::Sprite midLine{-5, -SCREEN_HEIGHT / 2, 10, 1024, "assets/textures/midline_10x1024.png"};
    leng::Renderer2D renderer;
    leng::Camera2D camera;
};

#endif // PLAY_STATE_H
