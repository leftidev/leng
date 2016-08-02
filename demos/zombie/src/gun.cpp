#include "gun.h"

namespace leng {
    
Gun::Gun(float x, float y, float width, float height, const std::string& path, glm::fvec2 Direction) : Entity(x, y, width, height, path) {
    direction = Direction;
    bb.radius.x = 0.0f;
    bb.radius.y = 0.0f;
}

Gun::~Gun() {}

void Gun::update(const glm::vec2& Position, float angleInRadians, float deltaTime) {
    // Update position
    position = Position;

    // Update sprite
    sprite.update(position);
    
    // Make gun rotate towards cursor
    sprite.setAngle(angleInRadians);
}

} // namespace leng
