#ifndef ENTITY_H
#define ENTITY_H

#include "sprite.h"
#include "leng.h"

namespace leng {
    class Entity {
    public:
	Entity(float x, float y, float _width, float _height, const char* path);
	~Entity();
	void update();
	
	Position pos;
	float width, height;
	Box aabb;
	Sprite sprite;
	Velocity vel;
    };
} // namespace leng

#endif // ENTITY_H
