#include "projectile.h"

namespace leng {
    
Projectile::Projectile(float x, float y, float width, float height, const std::string& path, const glm::fvec2& Velocity) : Entity(x, y, width, height, path), velocity(Velocity) {	
	startPosition = position;
	PROJECTILE_REACH = 400;
	destroyed = false;
}

Projectile::~Projectile() { }

void Projectile::update(std::vector<Block*> blocks, std::vector<Enemy*> enemies, float deltaTime) {
    Entity::update();
    // Move on X-axis
    position.x += velocity.x * deltaTime;

    // Check collisions on X-axis
    applyCollisions(blocks, enemies);
}

void Projectile::applyCollisions(std::vector<Block*> blocks, std::vector<Enemy*> enemies) {
    // Collide with level tiles
    for(unsigned int i = 0; i < blocks.size(); i++) {
	if(collideWithTile(position, width, height, blocks[i])) {
	    if(blocks[i]->type == SOLID || blocks[i]->type == KILL || blocks[i]->type == KILLREVERSE || blocks[i]->type == DISAPPEARING) {
		destroyed = true;
	    }
	}
    }
    // Collide with enemies
    for(unsigned int i = 0; i < enemies.size(); i++) {
	if(collideWithTile(position, width, height, enemies[i])) {
	    destroyed = true;
	    enemies[i]->bubbled = true;
	}
    }
}

} // namespace leng
