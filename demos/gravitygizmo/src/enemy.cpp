#include "enemy.h"

namespace leng {
    
Enemy::Enemy(float x, float y, float width, float height, const char* path) : Entity(x, y, width, height, path) {
    velocity.y = 0.5f;
}

Enemy::~Enemy() { }

void Enemy::update(leng::Entity& ball, float deltaTime) {
    Entity::update();
}

} // namespace leng
