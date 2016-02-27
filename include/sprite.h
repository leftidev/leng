#ifndef SPRITE_H
#define SPRITE_H

#include "texture.h"
#include "vertex.h"

namespace leng {

class Sprite {
public:
    Sprite(float _x, float _y, float _width, float _height, const char* path);
    ~Sprite();

    Texture texture;
    float x, y;
    float width, height;
    Vertex vertex_data[4];
};

} // namespace leng

#endif // SPRITE_H
