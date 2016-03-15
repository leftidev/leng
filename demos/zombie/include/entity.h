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
	
	glm::vec2 pos;
	float width, height;
	Circle bb;
	Sprite sprite;
	Velocity vel;
	bool moving;
    };
} // namespace leng

#endif // ENTITY_H
