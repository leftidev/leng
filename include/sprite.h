#ifndef SPRITE2_H
#define SPRITE2_H

#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "leng.h"
#include "vertex.h"
#include "resource_manager.h"

namespace leng {

class Sprite {
public:
    Sprite(float x, float y, float Width, float Height, const std::string& path, float angle = 0.0f);
    Sprite(float x, float y, float Width, float Height);
    ~Sprite();
    
    void setAngle(float angle);
    glm::vec2 rotatePoint(const glm::vec2& Position, float angle);
    void update(const glm::vec2& Position);
    void originalDirection();
    void reverse();
    void flip();
    void reverseFlip();
    GLuint textureID;
    GLuint normalID;
    glm::vec2 position;
    float width, height;
    Vertex vertexData[4];
    Vertex3 vertexData2[4];
    ColorRGBA8 color;
};

} // namespace leng

#endif // SPRITE_H
