#ifndef ITEM_H
#define ITEM_H

#include "entity.h"

namespace leng {
class Item : public Entity {
public:
    Item(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f, const std::string& path = "", const std::string& itemName = "");
    ~Item();
    void update(float deltaTime);

    std::string name;
    bool render;
};
    
} // namespace leng

#endif // ITEM_H
