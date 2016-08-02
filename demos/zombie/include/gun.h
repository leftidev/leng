#ifndef GUN_H
#define GUN_H

#include "entity.h"

namespace leng {

class Gun : public Entity {
public:
    Gun(float x, float y, float width, float height, const std::string& path, glm::fvec2 Direction);
    ~Gun();

    void update(const glm::vec2& Position, float angleInRadians, float deltaTime);

    glm::fvec2 direction;

    float angleInRadians;
};

} // namespace leng

#endif // GUN_H
