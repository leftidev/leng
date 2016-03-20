#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "entity.h"
#include "input_manager.h"
#include "camera_2d.h"
#include "item.h"
#include "projectile.h"

namespace leng {

class Player : public Entity {
public:
    Player(float x, float y, float width, float height, const std::string& path);
    ~Player();
    void update(leng::InputManager* inputManager, leng::Camera2D* camera, float deltaTime);
    void pickupItem(leng::Item* item);
    void shootProjectile(std::vector<Projectile*>& projectiles);
	
    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;

    glm::vec2 mouseCoords;
    glm::vec2 centerPosition;
    glm::vec2 direction;
    float angleInRadians;
    float health = 100.0f;
    std::vector<Item*> inventory;
};

    
} // namespace leng

#endif // PLAYER_H
