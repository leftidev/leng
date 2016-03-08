#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"
#include "leng.h"

namespace leng {
    class Entity {
    public:
	Entity(float x, float y, float _width, float _height, const std::string& path);
	~Entity();
	void update(float deltaTime);
	
	Position pos;
	float width, height;
	Box aabb;
	Sprite sprite;
	Velocity vel;
	bool moving;
    };
} // namespace leng

#endif // ENTITY_H
