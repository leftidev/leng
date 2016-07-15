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

    MOVE_VELOCITY = 1.5f;
    JUMP_VELOCITY = 2.25f;
    MAX_GRAVITY_VELOCITY = 2.5f;
    GRAVITY = 0.20f;
}

Player::~Player() {}
    
void Player::update(std::vector<leng::Block*> blocks, float deltaTime) {
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
    if(velocity.y < -MAX_GRAVITY_VELOCITY) {
    	velocity.y = -MAX_GRAVITY_VELOCITY;
    }
    if(velocity.y > MAX_GRAVITY_VELOCITY) {
    	velocity.y = MAX_GRAVITY_VELOCITY;
    }

    position.y += velocity.y * deltaTime;

    // Assume player is in air, this makes player fall off platform ledges
    inAir = true;
    // Check collisions on Y-axis
    applyCollisions(glm::fvec2(0.0f, velocity.y), blocks);
   
    // Check movement on x-axis
    if(rightHeld) {
	velocity.x = MOVE_VELOCITY;
    } else if(leftHeld) {
	velocity.x = -MOVE_VELOCITY;
    } else {
	velocity.x = 0.0f;
    }
    
    position.x += velocity.x * deltaTime;

    // Check collisions on X-axis
    applyCollisions(glm::fvec2(velocity.x, 0.0f), blocks);
}

// Collisions
void Player::applyCollisions(glm::fvec2 velocity, std::vector<Block*> blocks) {
	// Collide with level tiles
	for (unsigned int i = 0; i < blocks.size(); i++) {
	    if (collideWithTile(position, width, height, blocks[i])) {
		    // Collide from left
		    if (velocity.x > 0) {
			position.x = blocks[i]->position.x - width;
		    }
		    // Collide from right
		    else if (velocity.x < 0) {
			position.x = blocks[i]->position.x + blocks[i]->width;
		    }
		    if(normalGravity) {
			// Collide from below
			if (velocity.y > 0) {
			    velocity.y = 0;
			    position.y = blocks[i]->position.y - height;
			    inAir = true;
			}
			// Collide from above
			else if (velocity.y < 0) {
			    velocity.y = 0;
			    position.y = blocks[i]->position.y + blocks[i]->height;
			    inAir = false;
			    jumped = false;
			    canDoubleJump = false;
			}
		    } else {
			// Collide from below
			if (velocity.y > 0) {
			    velocity.y = 0;
			    position.y = blocks[i]->position.y - height;
			    inAir = false;
			    jumped = false;
			    canDoubleJump = false;
			
			}
			// Collide from above
			else if (velocity.y < 0) {
			    velocity.y = 0;
			    position.y = blocks[i]->position.y + blocks[i]->height;
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
	velocity.y = JUMP_VELOCITY;
    } else {
	velocity.y = -JUMP_VELOCITY;
    }
}

void Player::doubleJump() {
    if(canDoubleJump) {
	inAir = true;
	canDoubleJump = false;

	if(normalGravity) {
	    velocity.y = JUMP_VELOCITY;
	} else {
	    velocity.y = -JUMP_VELOCITY;
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
