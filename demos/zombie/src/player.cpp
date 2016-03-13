#include "player.h"

namespace leng {

Player::Player(float x, float y, float width, float height, const std::string& path) : Entity(x, y, width, height, path) {
    upHeld = false;
    downHeld = false;
    rightHeld = false;
    leftHeld = false;
    
    vel.y = 0.5f;
    vel.x = 0.5f;
}

Player::~Player() { }
    
void Player::update(float deltaTime) {
    Entity::update(deltaTime);

    if(upHeld) {
	pos.y += vel.y * deltaTime;
    }
    if(downHeld) {
	pos.y -= vel.y * deltaTime;
    }
    if(rightHeld) {
	pos.x += vel.x * deltaTime;
    }
    if(leftHeld) {
	pos.x -= vel.x * deltaTime;
    }

}

} // namespace leng
