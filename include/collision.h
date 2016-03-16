#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include "../demos/zombie/include/entity.h"
#include "leng.h"

namespace leng {

bool doBoxesIntersect(Box a, Box b);
bool doCirclesIntersect(Entity* agent, Entity* agent2);
bool collideWithCircle(Entity* agent, Entity* agent2);
//void collideWithTile(glm::vec2 tilePos);
} // namespace leng

#endif // COLLISION_H
