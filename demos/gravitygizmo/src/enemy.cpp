#include "enemy.h"
#include <iostream>
namespace leng {
    
Enemy::Enemy(float x, float y, float width, float height, const char* path, EnemyType Type, glm::fvec2 Velocity) : Entity(x, y, width, height, path), type(Type) {
    velocity.y = Velocity.x;
    velocity.x = Velocity.y;

    destroyed = false;
    bubbled = false;
    inAir = true;
    jumped = false;

    GRAVITY = 0.15f;
    JUMP_VELOCITY = 3.0f;
}

Enemy::~Enemy() { }

void Enemy::update(std::vector<leng::Block*> blocks, float deltaTime) {
    Entity::update();

    // If bubbled, freeze the enemy
    if (!bubbled) {
	if (type == JUMPING || type == REVERSEJUMPING || type == X_MOVINGJUMPING) {
	    if (!jumped && !inAir) {
		// Normal jumping
		applyJump();
	    }

	    // Player is in air, apply gravity
	    if (inAir) {
		jumped = true;
		if (type == JUMPING || type == X_MOVINGJUMPING) {
		    velocity.y -= GRAVITY;
		}
		if (type == REVERSEJUMPING) {
		    velocity.y += GRAVITY;
		}
	    }

	    // Move on Y-axis
	    position.y += velocity.y * deltaTime;

	    // Assume player is in air, this makes player fall off platform ledges
	    inAir = true;

	    // Check collisions on Y-axis
	    applyCollisions(glm::fvec2(0.0f, velocity.y), blocks);
	}
	if (type == X_MOVING || type == X_MOVINGJUMPING) {
	    // Move on X-axis
	    position.x += velocity.x * deltaTime;

	    // Check collisions on X-axis
	    applyCollisions(glm::fvec2(velocity.x, 0.0f), blocks);
	}
    }
}

void Enemy::applyCollisions(glm::fvec2 Velocity, std::vector<Block*> blocks) {
    // Collide with level tiles
    for (unsigned int i = 0; i < blocks.size(); i++) {
	if(collideWithTile(position, width, height, blocks[i])) {
	    if(blocks[i]->type == SOLID || blocks[i]->type == DISAPPEARING) {
		// Collide from left
		if (Velocity.x > 0) {
		    velocity.x *= -1;
		    position.x = blocks[i]->position.x - width;
		}
		// Collide from right
		else if (Velocity.x < 0) {
		    velocity.x *= -1;
		    position.x = blocks[i]->position.x + blocks[i]->width;
		}
		if (type == JUMPING || type == X_MOVINGJUMPING) {
		    // Collide from below
		    if (Velocity.y > 0) {
			velocity.y = 0;
			position.y = blocks[i]->position.y - height;
			inAir = true;
		    }
		    // Collide from above
		    else if (Velocity.y < 0) {
			velocity.y = 0;
			position.y = blocks[i]->position.y + blocks[i]->height;
			inAir = false;
			jumped = false;
		    }
		} else if (type == REVERSEJUMPING) {
		    // Collide from below
		    if (Velocity.y > 0) {
			velocity.y = 0;
			position.y = blocks[i]->position.y - height;
			inAir = false;
			jumped = false;			
		    }
		    // Collide from above
		    else if (Velocity.y < 0) { 
			velocity.y = 0;
			position.y = blocks[i]->position.y + blocks[i]->height;
			inAir = true;
		    }
		}
	    }
	}	
    }
}

void Enemy::applyJump() {
    inAir = true;
    jumped = true;

    if (type == JUMPING || X_MOVINGJUMPING) {
	velocity.y = JUMP_VELOCITY;
    }
    if (type == REVERSEJUMPING) {
	velocity.y = -JUMP_VELOCITY;
    }
}
    
} // namespace leng
