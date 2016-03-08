#include "sprite.h"

namespace leng {

Sprite::Sprite(float x, float y, float Width, float Height, const std::string& path) {
    textureID = leng::ResourceManager::getTexture(path).id;

    pos.x = x;
    pos.y = y;
    width = Width;
    height = Height;
    
    // Top right
    vertexData[0].setPosition(pos.x + width, pos.y + height);
    vertexData[0].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData[1].setPosition(pos.x + width, pos.y);
    vertexData[1].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData[2].setPosition(pos.x, pos.y);
    vertexData[2].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData[3].setPosition(pos.x, pos.y + height);
    vertexData[3].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData[3].setUV(0.0f, 1.0f);	
}
    
Sprite::~Sprite() { }
    
} // namespace leng
