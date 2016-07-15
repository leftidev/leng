#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "block.h"
#include "input_manager.h"
#include "camera_2d.h"
#include "collision.h"

namespace leng {

class Player : public Entity {
public:
    Player(float x, float y, float width, float height, const std::string& path);
    ~Player();
    void update(std::vector<leng::Block*> blocks, float deltaTime);
    void applyCollisions(glm::fvec2 velocity, std::vector<Block*> blocks);
    void jump();
    void doubleJump();
    void gravityBendInvert();
    void gravityBend();
    
    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;
    bool inAir;
    bool jumped;
    bool canDoubleJump;
    bool normalGravity;
    
    float GRAVITY;
};

    
} // namespace leng

#endif // PLAYER_H
