#ifndef LENG_H
#define LENG_H

#include <GL/glew.h>

namespace leng {

struct Normal {
    float x;
    float y;
    float z;
};

struct Texture {
    GLuint id;
    int width;
    int height;
};

struct Position {
    float x;
    float y;
};
struct Position3D {
    float x;
    float y;
    float z;
};
struct ColorRGBA8 {
ColorRGBA8() : r(0), g(0), b(0), a(0) { }
ColorRGBA8(float R, float G, float B, float A) :
    r(R), g(G), b(B), a(A) { }

    float r;
    float g;
    float b;
    float a;
};

struct UV {
    float u;
    float v;
};

struct Velocity {
    float x;
    float y;
};

struct Box {
    float x, y;
    float width, height;
};

} // namespace leng

#endif // LENG_H
