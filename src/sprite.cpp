#include "sprite.h"

namespace leng {

Sprite::Sprite(float _x, float _y, float _width, float _height, const char* path) {
    x = _x;
    y = _y;
    width = _width;
    height = _height;

    texture.init(path);
	
    // Top right
    vertex_data[0].set_position(x + width, y + height);
    vertex_data[0].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[0].set_uv(1.0f, 1.0f);
    // Bottom right
    vertex_data[1].set_position(x + width, y);
    vertex_data[1].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[1].set_uv(1.0f, 0.0f);
    // Bottom left
    vertex_data[2].set_position(x, y);
    vertex_data[2].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[2].set_uv(0.0f, 0.0f);
    // Top left
    vertex_data[3].set_position(x, y + height);
    vertex_data[3].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[3].set_uv(0.0f, 1.0f);	
}
    
Sprite::~Sprite() { }
    
} // namespace leng
