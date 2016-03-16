#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

namespace leng {
    class Item : public Entity {
    public:
	Item(float x, float y, float width, float height, const std::string& path);
	~Item();
	void update(float deltaTime);

    };
    
} // namespace leng

#endif // ITEM_H
