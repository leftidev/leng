#include "enemy.h"

namespace leng {

Enemy::Enemy(float x, float y, float width, float height, const std::string& path) : Entity(x, y, width, height, path) {
    vel.y = 0.05f;
    vel.x = 0.05f;
}

Enemy::~Enemy() { }
    
void Enemy::update(leng::Player* player, float deltaTime) {
    Entity::update(deltaTime);
    
    // Make enemy rotate towards player
    direction = glm::normalize(player->pos - pos);
    angleInRadians = std::atan2(direction.y, direction.x);
    sprite.setAngle(angleInRadians);

    // Enemy movement towards rotation (player)
    glm::vec2 enemySpeed = glm::vec2(vel.x, vel.y);
    pos += direction * enemySpeed * deltaTime;
}

} // namespace leng
