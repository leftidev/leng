#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "input_manager.h"
#include "camera_2d.h"
#include "collision.h"

#include "block.h"
#include "enemy.h"
#include "projectile.h"

enum Direction {
    RIGHT,
    LEFT
};
    
namespace leng {


class Player : public Entity {
public:
    Player(float x, float y, float width, float height, const std::string& path);
    ~Player();
    void update(std::vector<leng::Block*> blocks, std::vector<Enemy*> enemies, float deltaTime);
    void applyCollisions(glm::fvec2 Velocity, std::vector<Block*> blocks, std::vector<Enemy*> enemies);
    void jump();
    void doubleJump();
    void gravityBendInvert();
    void gravityBend();
    void restart();
    void shootBubble();
    
    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;
    bool inAir;
    bool jumped;
    bool canDoubleJump;
    bool normalGravity;
    bool respawn;
    
    Direction direction;
    
    bool levelCompleted;

    float MAX_MOVE_VELOCITY;
    float JUMP_VELOCITY;
    float GRAVITY;
    float MAX_GRAVITY_VELOCITY;
    float ACCELERATION;
    int deaths;
    
    glm::vec2 startPosition;

    Projectile* bubble = nullptr;
};

    
} // namespace leng

#endif // PLAYER_H
