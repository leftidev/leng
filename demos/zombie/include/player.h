#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

namespace leng {

class Player : public Entity {
public:
    Player(float x, float y, float width, float height, const std::string& path);
    ~Player();
    void update(float deltaTime);

    bool upHeld;
    bool downHeld;
    bool leftHeld;
    bool rightHeld;
};

    
} // namespace leng

#endif // PLAYER_H
