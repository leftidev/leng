#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include "block.h"
#include "enemy.h"
#include "collision.h"

namespace leng {
    
class Projectile : public Entity {
public:
    Projectile(float x, float y, float width, float height, const std::string& path, const glm::fvec2& Velocity);
    ~Projectile();

    void update(std::vector<Block*> blocks, std::vector<Enemy*> enemies, float deltaTime);
    void applyCollisions(std::vector<Block*> blocks, std::vector<Enemy*> enemies);

    bool destroyed;
    int PROJECTILE_REACH;
    glm::fvec2 velocity;
    glm::vec2 startPosition;
};

} // namespace leng

#endif // PROJECTILE_H 
