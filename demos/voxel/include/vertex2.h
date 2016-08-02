#ifndef VERTEX2_H
#define VERTEX2_H

#include <GL/glew.h>
#include "leng.h"

namespace leng {
    
// The vertex definition
struct Vertex2 {
    Vertex2(float x, float y, float z, float u, float v) {
	position.x = x;
	position.y = y;
	position.z = z;
	uv.u = u;
	uv.v = v;
    }
    // This is the position struct. When you store a struct or a class
    // inside of another struct or class, it is called composition. This is
    // layed out exactly the same in memory as if we had float position[2],
    // but doing it this way makes more sense.
    Position3D position;

    // 4 bytes for the r, g, b, a color
    //ColorRGBA8 color;

    // UV texture coordinates
    UV uv;
/*
    void setPosAndUV(float x, float y, float z, float u, float v) {
	position.x = x;
	position.y = y;
	position.z = z;
	uv.u = u;
	uv.v = v;
    }

    void setColor(float r, float g, float b, float a) {
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
    }
*/
};

} // namespace leng

#endif // VERTEX_H
