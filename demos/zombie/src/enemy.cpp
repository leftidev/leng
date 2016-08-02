#include "enemy.h"
#include <iostream>
namespace leng {

Enemy::Enemy(float x, float y, float width, float height, const std::string& path, glm::fvec2 Velocity) : Entity(x, y, width, height, path) {
    velocity = Velocity;
}

Enemy::~Enemy() { }
    
void Enemy::update(leng::Player* player, float deltaTime) {
    Entity::update();
    
    // Make enemy rotate towards player
    direction = glm::normalize(player->position - position);
    angleInRadians = std::atan2(direction.y, direction.x);
    sprite.setAngle(angleInRadians);

    // Enemy movement towards rotation (player)
    glm::vec2 enemySpeed = glm::vec2(velocity.x, velocity.y);
    position += direction * enemySpeed * deltaTime;
    //std::cout << position.x << std::endl;
}

} // namespace leng
