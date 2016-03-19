#include "projectile.h"
#include <iostream>

namespace leng {

Projectile::Projectile(float x, float y, float width, float height, const std::string& path, glm::fvec2 Velocity, glm::fvec2 Direction) : Entity(x, y, width, height, path) {
    velocity = Velocity;
    direction = Direction;
    bb.radius.x = 4.0f;
    bb.radius.y = 4.0f;
}

Projectile::~Projectile() {}

void Projectile::update(float deltaTime) {
    // Update position
    position.x += direction.x * velocity.x * deltaTime;
    position.y += direction.y * velocity.y * deltaTime;
    // Update bounding box
    bb.position.x = position.x;
    bb.position.y = position.y;
    // Update sprite
    sprite.update(position);
}

}
