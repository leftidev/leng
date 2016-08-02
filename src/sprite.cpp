#include "sprite.h"
#include <iostream>

namespace leng {

Sprite::Sprite(float x, float y, float Width, float Height, const std::string& path, float angle) {
    textureID = leng::ResourceManager::getTexture(path).id;
    normalID = leng::ResourceManager::getTexture(path + "_n").id;
    
    position.x = x;
    position.y = y;
    width = Width;
    height = Height;

    color = ColorRGBA8(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Top right
    vertexData[0].setPosition(position.x + width, position.y + height);
    vertexData[0].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData[1].setPosition(position.x + width, position.y);
    vertexData[1].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData[2].setPosition(position.x, position.y);
    vertexData[2].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData[3].setPosition(position.x, position.y + height);
    vertexData[3].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[3].setUV(0.0f, 1.0f);

    // Top right
    vertexData2[0].setPosition(position.x + width, position.y + height);
    vertexData2[0].color = color;
    vertexData2[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData2[1].setPosition(position.x + width, position.y);
    vertexData2[1].color = color;
    vertexData2[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData2[2].setPosition(position.x, position.y);
    vertexData2[2].color = color;
    vertexData2[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData2[3].setPosition(position.x, position.y + height);
    vertexData2[3].color = color;
    vertexData2[3].setUV(0.0f, 1.0f);	

    setAngle(angle);
}
Sprite::Sprite(float x, float y, float Width, float Height) {
    position.x = x;
    position.y = y;
    width = Width;
    height = Height;
    
    // Top right
    vertexData2[0].setPosition(position.x + width, position.y + height);
    vertexData2[0].color = color;
    vertexData2[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData2[1].setPosition(position.x + width, position.y);
    vertexData2[1].color = color;
    vertexData2[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData2[2].setPosition(position.x, position.y);
    vertexData2[2].color = color;
    vertexData2[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData2[3].setPosition(position.x, position.y + height);
    vertexData2[3].color = color;
    vertexData2[3].setUV(0.0f, 1.0f);	
}
    
Sprite::~Sprite() { }

void Sprite::setAngle(float angle) {
    glm::vec2 halfDimensions(width / 2.0f, height / 2.0f);

    // Get points origin at center
    glm::vec2 tr(halfDimensions.x, halfDimensions.y);
    glm::vec2 br(halfDimensions.x, -halfDimensions.y);
    glm::vec2 bl(-halfDimensions.x, -halfDimensions.y);
    glm::vec2 tl(-halfDimensions.x, halfDimensions.y);

    // Rotate the points
    tr = rotatePoint(tr, angle) + halfDimensions;
    br = rotatePoint(br, angle) + halfDimensions;
    bl = rotatePoint(bl, angle) + halfDimensions;
    tl = rotatePoint(tl, angle) + halfDimensions;

    // Top right
    vertexData[0].setPosition(position.x + tr.x, position.y + tr.y);
    vertexData[0].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData[1].setPosition(position.x + br.x, position.y + br.y);
    vertexData[1].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData[2].setPosition(position.x + bl.x, position.y + bl.y);
    vertexData[2].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData[3].setPosition(position.x + tl.x, position.y + tl.y);
    vertexData[3].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[3].setUV(0.0f, 1.0f);

    // Top right
    vertexData2[0].setPosition(position.x + tr.x, position.y + tr.y);
    // Bottom right
    vertexData2[1].setPosition(position.x + br.x, position.y + br.y);
    // Bottom left
    vertexData2[2].setPosition(position.x + bl.x, position.y + bl.y);
    // Top left
    vertexData2[3].setPosition(position.x + tl.x, position.y + tl.y);
}

glm::vec2 Sprite::rotatePoint(const glm::vec2& Position, float angle) {
    glm::vec2 newV;
    newV.x = Position.x * cos(angle) - Position.y * sin(angle);
    newV.y = Position.x * sin(angle) + Position.y * cos(angle);

    return newV;
}

void Sprite::update(const glm::vec2& Position) {
    position = Position;
    
    // Update sprite
    vertexData[0].setPosition(position.x + width, position.y + height);
    vertexData[1].setPosition(position.x + width, position.y);
    vertexData[2].setPosition(position.x, position.y);
    vertexData[3].setPosition(position.x, position.y + height);

    // Update sprite
    vertexData2[0].setPosition(position.x + width, position.y + height);
    vertexData2[1].setPosition(position.x + width, position.y);
    vertexData2[2].setPosition(position.x, position.y);
    vertexData2[3].setPosition(position.x, position.y + height);

    vertexData2[0].color = color;
    vertexData2[1].color = color;
    vertexData2[2].color = color;
    vertexData2[3].color = color;
}
    
} // namespace leng
