#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "game_state.h"
#include "window.h"
#include "input_manager.h"
#include "camera_2d.h"
#include "shader.h"
#include "sprite.h"
#include "renderer.h"
#include "player.h"
#include "light.h"
#include "chunk.h"
#include "enemy.h"
#include "collision.h"
#include "item.h"
#include "timer.h"
#include "projectile.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

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
    leng::Camera2D* camera = new leng::Camera2D;
    leng::Renderer* renderer = new leng::Renderer;
    leng::Chunk* chunk = new leng::Chunk(0);
// Build and compile our shader program
    leng::Shader lightingShader{"assets/shaders/lighting.vert", "assets/shaders/lighting.frag"};
    leng::Shader lampShader{"assets/shaders/lamp.vert", "assets/shaders/lamp.frag"};

    glm::vec3 pointLightPositions[4] = {
	glm::vec3(1500, 1500, 1.0f), // white
	glm::vec3(200, 200, 1.0f), // red
	glm::vec3(300, 300, 1.0f), // blue
	glm::vec3(700, 700, 5.0f) // green
    };

    leng::DirectionalLight* directionalLight = new leng::DirectionalLight;
    leng::PointLight* pointLight1 = new leng::PointLight;
    leng::PointLight* pointLight2 = new leng::PointLight;
    leng::PointLight* pointLight3 = new leng::PointLight;
    leng::PointLight* pointLight4 = new leng::PointLight;

    leng::Player* player = new leng::Player{1500, 1500, 64, 64, "assets/textures/soldier.png"};
    std::vector<leng::Enemy*> enemies;
    leng::Item* item = new leng::Item{1800, 1800, 32, 32, "assets/textures/simple_axe.png", "Hand Gun"};
    bool freecam = false;
    bool normalMapping = true;
    leng::Timer timer;
    std::vector<leng::Projectile*> projectiles;
    int spawnPosition = 0;
    int spawnPositionX = 0;
    int spawnPositionY = 0;
};

#endif // PLAY_STATE_H
