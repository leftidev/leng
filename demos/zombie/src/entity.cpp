#include "entity.h"

namespace leng {

Entity::Entity(float x, float y, float _width, float _height, const std::string& path) : sprite(x, y, _width, _height, path) {
    pos.x = x;
    pos.y = y;
    width = _width;
    height = _height;
    
    moving = false;
    
    // AABB Origin at center
    bb.position.x = pos.x;
    bb.position.y = pos.y;
    bb.radius.x = 16.0f;
    bb.radius.y = 16.0f;
    
    vel.x = 0.0f;
    vel.y = 0.0f;
}
    
Entity::~Entity() { }
    
void Entity::update(float delta_time) {
    if(moving) {
	// Update position
	pos.x += vel.x * delta_time;
	pos.y += vel.y * delta_time;
    }
    // Update bounding box
    bb.position.x = pos.x;
    bb.position.y = pos.y;
    // Update sprite
    sprite.update(pos);
}

} // namespace leng
