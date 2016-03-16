#include "item.h"

namespace leng {

Item::Item(float x, float y, float width, float height, const std::string& path) : Entity(x, y, width, height, path) {

}

void Item::update(float deltaTime) {
    Entity::update(deltaTime);
}
  
} // namespace leng
