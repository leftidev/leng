#ifndef PLAYER_H
#define PLAYER_H

#include "../../../include/entity.h"

namespace leng {

class Player : public Entity {
public:
    Player(float x, float y, float width, float height, const char* path);
    ~Player();
    void update(float delta_time);

    bool up_held;
    bool down_held;
};

    
} // namespace leng

#endif // PLAYER_H
