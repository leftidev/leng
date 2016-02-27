#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include "leng.h"

namespace leng {

bool do_boxes_intersect(Box a, Box b) {
    return (std::abs(a.x - b.x) * 2 <= (a.width + b.width)) &&
	(std::abs(a.y - b.y) * 2 <= (a.height + b.height));
}

} // namespace leng

#endif // COLLISION_H
