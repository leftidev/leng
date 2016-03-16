#include "renderer_2d.h"

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
    
void Renderer2D::initVAO(leng::Shader& shader) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Enable shader attributes
    shader.enableAttribute("position", 2, 8, (GLvoid*)0);
    shader.enableAttribute("color", 4, 8, (GLvoid*)(2 * sizeof(GLfloat)));
    shader.enableAttribute("text_coord", 2, 8, (GLvoid*)(6 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}
    /*    
void Renderer2D::updateVertices(leng::Sprite& sprite) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sprite.vertexData), sprite.vertexData, GL_STATIC_DRAW);
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
    */
} // namespace leng
