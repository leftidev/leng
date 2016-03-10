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
    leng::Player player{-SCREEN_WIDTH / 2, 0, 64, 64, "assets/textures/soldier.png"};
    leng::Renderer2D renderer;
    leng::Camera2D camera;
};

#endif // PLAY_STATE_H
