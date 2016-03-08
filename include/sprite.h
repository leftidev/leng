#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "leng.h"
#include "vertex.h"
#include "leng.h"

namespace leng {

class Sprite {
public:
    Sprite(float x, float y, float Width, float Height, const std::string& path);
    ~Sprite();

    Texture texture;
    Position pos;
    float width, height;
    Vertex vertexData[4];
};

} // namespace leng

#endif // SPRITE_H
