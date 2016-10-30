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
    respawn = false;
    deathFlicker = true;
    
    direction = Direction::RIGHT;
    
    MAX_MOVE_VELOCITY = 1.0f;
    JUMP_VELOCITY = 1.40f;
    MAX_GRAVITY_VELOCITY = 2.0f;
    GRAVITY = 0.10f;
    ACCELERATION = 0.35;
    
    deaths = 0;
    
    levelCompleted = false;

    startPosition.x = x;
    startPosition.y = y;
}

Player::~Player() {
    delete bubble;
}
    
void Player::update(std::vector<leng::Block*> blocks, std::vector<Enemy*> enemies, float deltaTime) {
    Entity::update();
    
    if(!deathFlicker) {
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
	applyCollisions(glm::fvec2(0.0f, velocity.y), blocks, enemies);
   
	// Check movement on x-axis
	if(rightHeld) {
	    direction = Direction::RIGHT;
	    if(normalGravity) {
		sprite.originalDirection();
	    } else {
		sprite.flipY();
	    }

	    // Apply acceleration
	    velocity.x += ACCELERATION;
	    if (velocity.x > MAX_MOVE_VELOCITY) {
		velocity.x = MAX_MOVE_VELOCITY;
	    }
	} else if(leftHeld) {
	    direction = Direction::LEFT;
	    if(normalGravity) {
		sprite.flipX();
	    } else {
		sprite.flipXY();
	    }

	    // Apply acceleration
	    velocity.x -= ACCELERATION;
	    if (velocity.x < -MAX_MOVE_VELOCITY) {
		velocity.x = -MAX_MOVE_VELOCITY;
	    }
	} else {
	    velocity.x = 0.0f;
	}
    
	position.x += velocity.x * deltaTime;

	// Check collisions on X-axis
	applyCollisions(glm::fvec2(velocity.x, 0.0f), blocks, enemies);
    } else {
	
	if(deathFlickerCounter == 3) {
	    deathFlickerCounter = 0;
	    deathFlicker = false;
	}
	
	if(alphaDown) {
	    sprite.color.a -= 0.10f;
	    if(sprite.color.a <= 0.0f) {
		alphaDown = false;
		alphaUp = true;
	    }
	}
	if(alphaUp) {
	    sprite.color.a += 0.10f;
	    if(sprite.color.a >= 1.0f) {
		alphaUp = false;
		alphaDown = true;
		deathFlickerCounter++;
	    }
	}

    }
}

// Collisions
    void Player::applyCollisions(glm::fvec2 Velocity, std::vector<Block*> blocks, std::vector<Enemy*> enemies) {
    // Collide with level tiles
    for (unsigned int i = 0; i < blocks.size(); i++) {
	if (collideWithTile(position, width, height, blocks[i])) {
	    if(blocks[i]->type == SOLID || blocks[i]->type == DISAPPEARING) {
		// Collide from left
		if (Velocity.x > 0) {
		    position.x = blocks[i]->position.x - width;
		}
		// Collide from right
		else if (Velocity.x < 0) {
		    position.x = blocks[i]->position.x + blocks[i]->width;
		}
		if(normalGravity) {
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
			canDoubleJump = false;
		    }
		} else {
		    // Collide from below
		    if (Velocity.y > 0) {
			velocity.y = 0;
			position.y = blocks[i]->position.y - height;
			inAir = false;
			jumped = false;
			canDoubleJump = false;
			
		    }
		    // Collide from above
		    else if (Velocity.y < 0) { 
			velocity.y = 0;
			position.y = blocks[i]->position.y + blocks[i]->height;
			inAir = true;
		    }
		}
	    } else if(blocks[i]->type == KILL || blocks[i]->type == KILLREVERSE) {
		respawn = true;
		restart();
		deaths++;
	    } else if(blocks[i]->type == EXIT) {
		levelCompleted = true;
	    }
	}
    }

    // Collide with enemies
    for (unsigned int i = 0; i < enemies.size(); i++) {
	if (collideWithTile(position, width, height, enemies[i])) {
	    if(enemies[i]->bubbled) {
		enemies[i]->destroyed = true;

	    } else {
		respawn = true;
		restart();
		deaths++;
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
	
	if(direction == Direction::RIGHT) {
	    sprite.flipY();
	} else if (direction == Direction::LEFT) {
	    sprite.flipXY();
	}
    }
}

void Player::gravityBend() {
    if(!normalGravity && !inAir) {
	normalGravity = true;

	if(direction == Direction::RIGHT) {
	    sprite.originalDirection();
	} else if (direction == Direction::LEFT) {
	    sprite.flipX();
	}
    }	
}
    
void Player::restart() {
    deathFlicker = true;
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    normalGravity = true;
    position.x = startPosition.x;
    position.y = startPosition.y;
}

void Player::shootBubble() {
    if(bubble == nullptr) {
	if(direction == Direction::RIGHT) {
	    bubble = new Projectile(position.x + width + 1, position.y, 52, 52, "assets/textures/bubble_78x78.png", glm::fvec2(1.0f, 0.0f));
	} else {
	    bubble = new Projectile(position.x - width - 1, position.y, 52, 52, "assets/textures/bubble_78x78.png", glm::fvec2(-1.0f, 0.0f));
	}
	
    }
}
    
} // namespace leng
