#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include <string>

#include "game_state.h"
#include "window.h"
#include "input_manager.h"
#include "shader.h"
#include "camera_2d.h"
#include "timer.h"
#include "renderer_2d.h"
#include "sprite_font.h"

#include "player.h"
#include "level.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class PlayState : public leng::GameState {
public:
    PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager, leng::Shader* Shader, int CurrentLevel);
    ~PlayState();

    void initLevel();
    void handleEvents(leng::InputManager* inputManager, float deltaTime) override;
    void update(float deltaTime) override;
    void draw() override;
    
private:    
    //leng::Shader shader{"assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag"};
    leng::Player* player = nullptr;
    leng::Level* level = nullptr;
    leng::Timer elapsedTimeTimer;
    leng::Camera2D camera;
    leng::Renderer2D renderer;
    leng::Shader* shader;

    leng::SpriteFont timeText{50000, 50000, 50, "assets/fonts/centurygothic.ttf", "Timer: xx.xx s.", {255, 255, 255, 255}};
    leng::SpriteFont levelText{50000, 50000, 50, "assets/fonts/centurygothic.ttf", "Level 10", {255, 255, 255, 255}};
    leng::SpriteFont deathsText{50000, 50000, 50, "assets/fonts/centurygothic.ttf", "Deaths: 100", {255, 255, 255, 255}};
    leng::SpriteFont enemiesText{50000, 50000, 50, "assets/fonts/centurygothic.ttf", "Enemies left: x", {255, 255, 255, 255}};
    
    int currentLevel;
    bool freeCam = false;
    float timeSinceLevelStart;
};

#endif // PLAY_STATE_H
