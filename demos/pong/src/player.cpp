#include "player.h"

namespace leng {

Player::Player(float x, float y, float width, float height, const char* path) : Entity(x, y, width, height, path) {
    up_held = false;
    down_held = false;

    vel.y = 5.0f;
}

Player::~Player() { }
    
void Player::update() {
    Entity::update();

    if(up_held) {
	pos.y += vel.y;
    }
    if(down_held) {
	pos.y -= vel.y;
    }
}

} // namespace leng
