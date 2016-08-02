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
	    if(enemies[i]->type == JUMPING || enemies[i]->type == X_MOVING || enemies[i]->type == STILL || enemies[i]->type == X_MOVINGJUMPING) {
		enemies[i]->sprite.textureID = leng::ResourceManager::getTexture("assets/textures/pacified_enemy_104x104.png").id;
		enemies[i]->sprite.position = enemies[i]->position;
		enemies[i]->sprite.width = 104;
		enemies[i]->sprite.height = 104;
	    } else {
		enemies[i]->sprite.textureID = leng::ResourceManager::getTexture("assets/textures/pacified_enemy_rev_104x104.png").id;
		enemies[i]->sprite.position = enemies[i]->position;
		enemies[i]->sprite.width = 104;
		enemies[i]->sprite.height = 104;
	    }
	}
    }
}

} // namespace leng
