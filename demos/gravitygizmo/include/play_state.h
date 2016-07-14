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

const int SCREEN_WIDTH = 1680;
const int SCREEN_HEIGHT = 1050;

class PlayState : public leng::GameState {
public:
    PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager);
    ~PlayState();

    void init() override;
    void handleEvents(leng::InputManager* inputManager, float deltaTime) override;
    void update(float deltaTime) override;
    void draw() override;
    void doCollisions();
    
private:
    leng::Shader shader{"assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag"};
    leng::SoundEffect ballHitsEnemy{"assets/sounds/ball_hits_enemy.wav"};
    //leng::Player player{-SCREEN_WIDTH / 2, 0, 52, 52, "assets/textures/gizmo_52x52.png"};
    leng::Enemy enemy{SCREEN_WIDTH / 2 - 24, 0, 78, 78, "assets/textures/enemy_black_78x78.png"};
    leng::Player player{100, 0, 52, 52, "assets/textures/gizmo_52x52.png"};

    leng::Entity ball{0, 0, 78, 78, "assets/textures/bubble_78x78.png"};
    leng::Sprite midLine{-5, -SCREEN_HEIGHT / 2, 52, 1050, "assets/textures/grass_block_52x52.png"};
    leng::Renderer2D renderer;
    leng::Camera2D camera;
    std::vector<leng::Entity*> tiles;

};

#endif // PLAY_STATE_H
