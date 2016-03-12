#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <GL/glew.h>

#include "leng.h"
#include "vertex.h"
#include "leng.h"
#include "resource_manager.h"

namespace leng {

class Sprite {
public:
    Sprite(float x, float y, float Width, float Height, const std::string& path);
    ~Sprite();

    GLuint textureID;
    Position pos;
    float width, height;
    Vertex vertexData[4];
};

} // namespace leng

#endif // SPRITE_H
