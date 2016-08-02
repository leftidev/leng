#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"

namespace leng {

class Projectile : public Entity {
public:
    Projectile(float x, float y, float width, float height, const std::string& path, glm::fvec2 Velocity, glm::fvec2 Direction);
    ~Projectile();

    void update(float deltaTime);

    glm::fvec2 direction;
};
    
} // namespace leng

#endif // PROJECTILE_H
