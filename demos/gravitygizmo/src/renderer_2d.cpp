#include "renderer_2d.h"
#include "SDL2/SDL_ttf.h"
namespace leng {
    
Renderer2D::Renderer2D() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // EBO indices for a quad
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 3;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;
}

Renderer2D::~Renderer2D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
    
void Renderer2D::initVAO(leng::Shader* shader) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    /*
    // Enable shader attributes
    shader->enableAttribute("position", 2, 8, (GLvoid*)0);
    shader->enableAttribute("color", 4, 8, (GLvoid*)(2 * sizeof(GLfloat)));
    shader->enableAttribute("text_coord", 2, 8, (GLvoid*)(6 * sizeof(GLfloat)));
    */
    
    // Tell OpenGL what attribute arrays we need
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    // This is the position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, position));
    // This is the color attribute pointer
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, color));
    // This is the UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3), (void*)offsetof(Vertex3, uv));
    
    glBindVertexArray(0);
}
  
void Renderer2D::updateVertices(leng::Sprite& sprite) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sprite.vertexData2), sprite.vertexData2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer2D::updateVertices(leng::SpriteFont& spriteFont) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(spriteFont.vertexData2), spriteFont.vertexData2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer2D::draw(leng::Sprite& sprite) {
    updateVertices(sprite);
    
    glBindTexture(GL_TEXTURE_2D, sprite.textureID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Renderer2D::drawText(leng::SpriteFont& spriteFont) {
    updateVertices(spriteFont);

    glBindTexture(GL_TEXTURE_2D, spriteFont.texture);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace leng
