#include "player.h"
#include <iostream>

namespace leng {

Player::Player(float x, float y, float width, float height, const std::string& path) : Entity(x, y, width, height, path) {
    upHeld = false;
    downHeld = false;
    rightHeld = false;
    leftHeld = false;

    inAir = true;
    jumped = true;
    canDoubleJump = false;
    normalGravity = true;
    
    GRAVITY = 0.25f;
}

Player::~Player() {}
    
void Player::update(std::vector<leng::Entity*> tiles, float deltaTime) {
    Entity::update();

    // Player is in air, apply gravity
    if (inAir) {
	jumped = true;
	if(normalGravity) {
	    velocity.y -= GRAVITY;	    
	} else {
	    velocity.y += GRAVITY;
	}
    } else {
	velocity.y = 0.0f;
    }
    if(velocity.y < -6.0f) {
    	velocity.y = -6.0f;
    }
    if(velocity.y > 6.0f) {
    	velocity.y = 6.0f;
    }

    position.y += velocity.y * deltaTime;

    // Assume player is in air, this makes player fall off platform ledges
    inAir = true;
    // Check collisions on Y-axis
    applyCollisions(glm::fvec2(0.0f, velocity.y), tiles);
    
    //velocity.y = 0.0f;
    
    // Check movement on x-axis
    if(rightHeld) {
	velocity.x = 1.5f;
    } else if(leftHeld) {
	velocity.x = -1.5f;
    } else {
	velocity.x = 0.0f;
    }
    
    position.x += velocity.x * deltaTime;

    // Check collisions on X-axis
    applyCollisions(glm::fvec2(velocity.x, 0.0f), tiles);
}

// Collisions
void Player::applyCollisions(glm::fvec2 velocity, std::vector<Entity*> tiles) {
	// Collide with level tiles
	for (unsigned int i = 0; i < tiles.size(); i++) {
	    if (collideWithTile(position, width, height, tiles[i])) {
		    // Collide from left
		    if (velocity.x > 0) {
			position.x = tiles[i]->position.x - width;
		    }
		    // Collide from right
		    else if (velocity.x < 0) {
			position.x = tiles[i]->position.x + tiles[i]->width;
		    }
		    if(normalGravity) {
			// Collide from below
			if (velocity.y > 0) {
			    velocity.y = 0;
			    position.y = tiles[i]->position.y - height;
			    inAir = true;
			}
			// Collide from above
			else if (velocity.y < 0) {
			    velocity.y = 0;
			    position.y = tiles[i]->position.y + tiles[i]->height;
			    inAir = false;
			    jumped = false;
			    canDoubleJump = false;
			}
		    } else {
			// Collide from below
			if (velocity.y > 0) {
			    velocity.y = 0;
			    position.y = tiles[i]->position.y - height;
			    inAir = false;
			    jumped = false;
			    canDoubleJump = false;
			
			}
			// Collide from above
			else if (velocity.y < 0) {
			    velocity.y = 0;
			    position.y = tiles[i]->position.y + tiles[i]->height;
			    inAir = true;			}

		    }
		}
	}
}

void Player::jump() {
    jumped = true;
    inAir = true;
    canDoubleJump = true;

    if(normalGravity) {
	velocity.y = 3.0f;
    } else {
	velocity.y = -3.0f;
    }
}

void Player::doubleJump() {
    if(canDoubleJump) {
	canDoubleJump = false;

	if(normalGravity) {
	    velocity.y = 3.0f;
	} else {
	    velocity.y = -3.0f;
	}
    }
}

void Player::gravityBendInvert() {
    if(normalGravity && !inAir) {
	normalGravity = false;
    }
}

void Player::gravityBend() {
    if(!normalGravity && !inAir) {
	normalGravity = true;
    }	
}

} // namespace leng
