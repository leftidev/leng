#include "player.h"

namespace leng {

Player::Player(float x, float y, float width, float height, const char* path) : Entity(x, y, width, height, path) {
    up_held = false;
    down_held = false;

    vel.y = 0.5f;
}

Player::~Player() { }
    
void Player::update(float delta_time) {
    Entity::update(delta_time);

    if(up_held) {
	pos.y += vel.y * delta_time;
    }
    if(down_held) {
	pos.y -= vel.y * delta_time;
    }
}

} // namespace leng
