#include "sprite.h"
#include <iostream>

namespace leng {

    Sprite::Sprite(float x, float y, float Width, float Height, const std::string& path, float angle) {
    textureID = leng::ResourceManager::getTexture(path).id;
    
    pos.x = x;
    pos.y = y;
    width = Width;
    height = Height;
    
    // Top right
    vertexData[0].setPosition(pos.x + width, pos.y + height);
    vertexData[0].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData[1].setPosition(pos.x + width, pos.y);
    vertexData[1].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData[2].setPosition(pos.x, pos.y);
    vertexData[2].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData[3].setPosition(pos.x, pos.y + height);
    vertexData[3].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[3].setUV(0.0f, 1.0f);

    setAngle(angle);
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
    vertexData[0].setPosition(pos.x + tr.x, pos.y + tr.y);
    vertexData[0].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData[1].setPosition(pos.x + br.x, pos.y + br.y);
    vertexData[1].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData[2].setPosition(pos.x + bl.x, pos.y + bl.y);
    vertexData[2].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData[3].setPosition(pos.x + tl.x, pos.y + tl.y);
    vertexData[3].setNormal(0.0f, 0.0f, -1.0f);
    vertexData[3].setUV(0.0f, 1.0f);
}

glm::vec2 Sprite::rotatePoint(glm::vec2 Pos, float angle) {
    glm::vec2 newV;
    newV.x = Pos.x * cos(angle) - Pos.y * sin(angle);
    newV.y = Pos.x * sin(angle) + Pos.y * cos(angle);

    return newV;
}

void Sprite::update(glm::vec2 Pos) {
    pos = Pos;
    
    // Update sprite
    vertexData[0].setPosition(pos.x + width, pos.y + height);
    vertexData[1].setPosition(pos.x + width, pos.y);
    vertexData[2].setPosition(pos.x, pos.y);
    vertexData[3].setPosition(pos.x, pos.y + height);
}
    
} // namespace leng
