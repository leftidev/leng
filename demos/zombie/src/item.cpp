#include "item.h"

namespace leng {

Item::Item(float x, float y, float width, float height, const std::string& path, const std::string& itemName) : Entity(x, y, width, height, path) {
	name = itemName;
	render = true;
}

Item::~Item() {}

void Item::update(float deltaTime) {
    Entity::update();
}
  
} // namespace leng
