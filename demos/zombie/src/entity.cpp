#include "entity.h"

namespace leng {

Entity::Entity(float x, float y, float _width, float _height, const std::string& path) : sprite(x, y, _width, _height, path) {
    position.x = x;
    position.y = y;
    width = _width;
    height = _height;
    
    moving = false;
    
    // AABB Origin at center
    bb.position.x = position.x;
    bb.position.y = position.y;
    bb.radius.x = 16.0f;
    bb.radius.y = 16.0f;
    
    velocity.x = 0.0f;
    velocity.y = 0.0f;
}
    
Entity::~Entity() { }
    
void Entity::update() {
    if(moving) {
	// Update position
	position.x += velocity.x;
	position.y += velocity.y;
    }
    // Update bounding box
    bb.position.x = position.x;
    bb.position.y = position.y;
    // Update sprite
    sprite.update(position);
}

} // namespace leng
