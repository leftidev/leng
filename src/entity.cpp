#include "entity.h"

namespace leng {

Entity::Entity(float x, float y, float _width, float _height, const char* path) : sprite(x, y, _width, _height, path) {
    pos.x = x;
    pos.y = y;
    width = _width;
    height = _height;
    
    moving = false;
    
    // AABB Origin at center
    aabb.x = pos.x + (width / 2);
    aabb.y = pos.y + (height / 2);
    aabb.width = width;
    aabb.height = height;

    vel.x = 0.0f;
    vel.y = 0.0f;
}
    
Entity::~Entity() { }
    
void Entity::update() {
    if(moving) {
	// Update position
	pos.x += vel.x;
	pos.y += vel.y;
    }
    // Update aabb
    aabb.x = pos.x + (width / 2);
    aabb.y = pos.y + (height / 2);	
    // Update sprite
    sprite.vertex_data[0].set_position(pos.x + width, pos.y + height);
    sprite.vertex_data[1].set_position(pos.x + width, pos.y);
    sprite.vertex_data[2].set_position(pos.x, pos.y);
    sprite.vertex_data[3].set_position(pos.x, pos.y + height);
}

} // namespace leng
