#include "sprite.h"

namespace leng {

Sprite::Sprite(float x, float y, float _width, float _height, const char* path) : texture(path) {
    pos.x = x;
    pos.y = y;
    width = _width;
    height = _height;
    
    // Top right
    vertex_data[0].set_position(pos.x + width, pos.y + height);
    vertex_data[0].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[0].set_uv(1.0f, 1.0f);
    // Bottom right
    vertex_data[1].set_position(pos.x + width, pos.y);
    vertex_data[1].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[1].set_uv(1.0f, 0.0f);
    // Bottom left
    vertex_data[2].set_position(pos.x, pos.y);
    vertex_data[2].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[2].set_uv(0.0f, 0.0f);
    // Top left
    vertex_data[3].set_position(pos.x, pos.y + height);
    vertex_data[3].set_color(1.0f, 1.0f, 1.0f, 1.0f);
    vertex_data[3].set_uv(0.0f, 1.0f);	
}
    
Sprite::~Sprite() { }
    
} // namespace leng
