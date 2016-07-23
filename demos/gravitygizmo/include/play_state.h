#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <vector>
#include <string>

#include "game_state.h"
#include "window.h"
#include "shader.h"
#include "sound.h"
#include "collision.h"
#include "renderer_2d.h"
#include "sprite.h"
#include "camera_2d.h"
#include "input_manager.h"
#include "sprite_font.h"
#include "timer.h"

#include "player.h"
#include "enemy.h"
#include "entity.h"
#include "level.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

const int SCREEN_WIDTH = 1680;
const int SCREEN_HEIGHT = 1050;

class PlayState : public leng::GameState {
public:
    PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager, int CurrentLevel);
    ~PlayState();

    void init() override;
    void initLevel();
    void handleEvents(leng::InputManager* inputManager, float deltaTime) override;
    void update(float deltaTime) override;
    void draw() override;
    void doCollisions();
    void restartLevel();
    void TTF();
    
private:
    leng::Shader shader{"assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag"};
    leng::SoundEffect ballHitsEnemy{"assets/sounds/ball_hits_enemy.wav"};
    leng::Player* player = nullptr;
    leng::Renderer2D renderer;
    leng::Camera2D camera;
    leng::SpriteFont timeText{500, 1000, 50, "assets/fonts/centurygothic.ttf", "Time: "};
    leng::Level* level = nullptr;
    leng::Timer elapsedTimeTimer;
    
    int currentLevel;
    bool freeCam = false;
    float timeSinceLevelStart;
    
};

#endif // PLAY_STATE_H
