#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "block.h"
#include "entity.h"
#include "collision.h"

enum EnemyType {
    STILL,
    X_MOVING,
    JUMPING,
    REVERSEJUMPING,
    X_MOVINGJUMPING
};

namespace leng {
    
class Enemy : public Entity {
public:
    Enemy(float x, float y, float width, float height, const char* path, EnemyType Type, glm::fvec2 Velocity);
    ~Enemy();
    void update(std::vector<leng::Block*> blocks, float deltaTime);
    void applyCollisions(glm::fvec2 Velocity, std::vector<Block*> blocks);
    void applyJump();
    
    bool destroyed;
    bool bubbled;
    bool inAir;
    bool jumped;

    float GRAVITY;
    float JUMP_VELOCITY;
    
    EnemyType type;
};

} //namespace leng

#endif // ENEMY_H
