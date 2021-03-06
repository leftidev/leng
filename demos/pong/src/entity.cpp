#include "entity.h"

namespace leng {

Entity::Entity(float x, float y, float _width, float _height, const std::string& path) : sprite(x, y, _width, _height, path) {
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
    
void Entity::update(float delta_time) {
    if(moving) {
	// Update position
	pos.x += vel.x * delta_time;
	pos.y += vel.y * delta_time;
    }
    // Update aabb
    aabb.x = pos.x + (width / 2);
    aabb.y = pos.y + (height / 2);	
    // Update sprite
    sprite.vertexData[0].setPosition(pos.x + width, pos.y + height);
    sprite.vertexData[1].setPosition(pos.x + width, pos.y);
    sprite.vertexData[2].setPosition(pos.x, pos.y);
    sprite.vertexData[3].setPosition(pos.x, pos.y + height);
}

} // namespace leng
