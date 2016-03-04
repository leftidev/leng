#ifndef ENEMY_H
#define ENEMY_H

#include "../../../include/entity.h"

namespace leng {
    
class Enemy : public Entity {
public:
    Enemy(float x, float y, float width, float height, const char* path);
    ~Enemy();
    void update(leng::Entity& ball, float delta_time);
};

} //namespace leng

#endif // ENEMY_H
