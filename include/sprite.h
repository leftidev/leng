#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "leng.h"
#include "vertex.h"
#include "leng.h"

namespace leng {

class Sprite {
public:
    Sprite(float x, float y, float _width, float _height, std::string path);
    ~Sprite();

    Texture texture;
    Position pos;
    float width, height;
    Vertex vertex_data[4];
};

} // namespace leng

#endif // SPRITE_H
