#include "player.h"
#include <iostream>

namespace leng {

Player::Player(float x, float y, float width, float height, const std::string& path) : Entity(x, y, width, height, path) {
    upHeld = false;
    downHeld = false;
    rightHeld = false;
    leftHeld = false;
    
    velocity.y = 0.35f;
    velocity.x = 0.35f;
}

Player::~Player() {
    for(unsigned int i = 0; i < inventory.size(); i++) {
	delete inventory[i];
    }
}
    
void Player::update(leng::InputManager* inputManager, leng::Camera2D* camera, float deltaTime) {
    Entity::update(deltaTime);

    if(upHeld) {
	position.y += velocity.y * deltaTime;
    }
    if(downHeld) {
	position.y -= velocity.y * deltaTime;
    }
    if(rightHeld) {
	position.x += velocity.x * deltaTime;
    }
    if(leftHeld) {
	position.x -= velocity.x * deltaTime;
    }
    
    // Make player rotate towards cursor
    mouseCoords = inputManager->getMouseCoords();
    mouseCoords = camera->convertScreenToWorld(mouseCoords);
    centerPosition = position + glm::vec2(width / 2, height / 2);
    direction = glm::normalize(mouseCoords - centerPosition);
    angleInRadians = std::atan2(direction.y, direction.x);
    sprite.setAngle(angleInRadians);
}

void Player::pickupItem(leng::Item* item) {
    leng::Item* pickup = new leng::Item;
    pickup->name = item->name;
    inventory.push_back(pickup);
    std::cout << "Item: " + pickup->name + " picked up." << std::endl;
}

void Player::shootProjectile(std::vector<Projectile*>& projectiles) {
    if (projectiles.size() < 10000) {
	leng::Projectile* projectile = new leng::Projectile(position.x + width / 2, position.y + height / 2, 8.0f, 8.0f, "assets/textures/bullet.png", glm::fvec2(0.4f, 0.4f), direction);
	projectiles.push_back(projectile);
    }
}
    
} // namespace leng
