#include "renderer.h"

namespace leng {
    
Renderer::Renderer(leng::ShaderProgram& shader_program) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    create_vertex_array(shader_program);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Renderer::create_vertex_array(leng::ShaderProgram& shader_program) {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Enable shader attributes
    shader_program.enable_attribute("position", 3, 8, (GLvoid*)0);
    shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    shader_program.enable_attribute("text_coord", 2, 8, (GLvoid*)(6 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

void Renderer::render() {
        // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         100.5f,  100.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Top Right
         100.5f, -100.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Bottom Right
        -100.5f, -100.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -100.5f,  100.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}



} // namespace leng
