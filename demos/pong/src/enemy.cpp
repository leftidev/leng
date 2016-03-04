#include "enemy.h"

namespace leng {
    
Enemy::Enemy(float x, float y, float width, float height, const char* path) : Entity(x, y, width, height, path) {
    vel.y = 5.0f;
}

Enemy::~Enemy() { }

    void Enemy::update(leng::Entity& ball, float delta_time) {
    Entity::update(delta_time);
    
    // Chase ball logic
    if(ball.vel.x > 0 && ball.pos.x > 0) {
	if(pos.y + height / 2 >= ball.pos.y + ball.height / 2) {
	    pos.y -= vel.y * delta_time;
	} else if (pos.y + height / 2 < ball.pos.y + ball.height / 2) {
	    pos.y += vel.y * delta_time;
	}
    }
}

} // namespace leng
