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
    ~Sprite();
    void setAngle(float angle);
    glm::vec2 rotatePoint(glm::vec2 Pos, float angle);
    void update(glm::vec2 Pos);
    GLuint textureID;
    GLuint normalID;
    glm::vec2 pos;
    float width, height;
    Vertex vertexData[4];
};

} // namespace leng

#endif // SPRITE_H
