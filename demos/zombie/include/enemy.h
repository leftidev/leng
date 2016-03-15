#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "player.h"

namespace leng {

class Enemy : public Entity {
public:
    Enemy(float x, float y, float width, float height, const std::string& path);
    ~Enemy();
    void update(leng::Player* player, float deltaTime);

    glm::vec2 direction;
    float angleInRadians;
};

    
} // namespace leng

#endif // ENEMY_H
