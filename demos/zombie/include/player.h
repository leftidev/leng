#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "input_manager.h"
#include "camera_2d.h"

namespace leng {

class Player : public Entity {
public:
    Player(float x, float y, float width, float height, const std::string& path);
    ~Player();
    void update(leng::InputManager* inputManager, leng::Camera2D* camera, float deltaTime);

    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;

    glm::vec2 mouseCoords;
    glm::vec2 centerPosition;
    glm::vec2 direction;
    float angleInRadians;
};

    
} // namespace leng

#endif // PLAYER_H
