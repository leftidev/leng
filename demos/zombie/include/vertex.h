#ifndef VERTEX3_H
#define VERTEX3_H

#include <GL/glew.h>
#include "leng.h"

namespace leng {
    
// The vertex definition
struct Vertex {
    // This is the position struct. When you store a struct or a class
    // inside of another struct or class, it is called composition. This is
    // layed out exactly the same in memory as if we had float position[2],
    // but doing it this way makes more sense.
    Position position;

    // 4 bytes for the r, g, b, a color
    Normal normal;

    // UV texture coordinates
    UV uv;

    void setPosition(float x, float y) {
	position.x = x;
	position.y = y;
    }

    void setNormal(float x, float y, float z) {
	normal.x = x;
	normal.y = y;
	normal.z = z;
    }

    void setUV(float u, float v) {
	uv.u = u;
	uv.v = v;
    }
};

    
// The vertex definition
struct Vertex2 {
    Vertex2(float x, float y, float x2, float y2, float z2, float u, float v) {
	position.x = x;
	position.y = y;
	normal.x = x2;
	normal.y = y2;
	normal.z = z2;
	uv.u = u;
	uv.v = v;
    }
    // This is the position struct. When you store a struct or a class
    // inside of another struct or class, it is called composition. This is
    // layed out exactly the same in memory as if we had float position[2],
    // but doing it this way makes more sense.
    Position position;

    // 4 bytes for the r, g, b, a color
    Normal normal;

    // UV texture coordinates
    UV uv;
};

} // namespace leng

#endif // VERTEX3_H
