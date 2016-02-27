#include "renderer.h"

namespace leng {
    
Renderer::Renderer(leng::ShaderProgram& shader_program) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    create_vertex_array(shader_program);

    // EBO indices
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 3;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;
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
    shader_program.enable_attribute("position", 2, 8, (GLvoid*)0);
    shader_program.enable_attribute("color", 4, 8, (GLvoid*)(2 * sizeof(GLfloat)));
    shader_program.enable_attribute("text_coord", 2, 8, (GLvoid*)(6 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}



void Renderer::update_vertices(leng::Sprite& sprite) {
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
         // Positions          // Colors                     // Texture Coords
	 sprite.vertex_data[0].position.x, sprite.vertex_data[0].position.y,  sprite.vertex_data[0].color.r, sprite.vertex_data[0].color.g, sprite.vertex_data[0].color.b, sprite.vertex_data[0].color.a,   sprite.vertex_data[0].uv.u, sprite.vertex_data[0].uv.v, // Top Right
	 sprite.vertex_data[1].position.x, sprite.vertex_data[1].position.y,  sprite.vertex_data[1].color.r, sprite.vertex_data[1].color.g, sprite.vertex_data[1].color.b, sprite.vertex_data[1].color.a,   sprite.vertex_data[1].uv.u, sprite.vertex_data[1].uv.v, // Bottom Right
	 sprite.vertex_data[2].position.x, sprite.vertex_data[2].position.y,  sprite.vertex_data[2].color.r, sprite.vertex_data[2].color.g, sprite.vertex_data[2].color.b, sprite.vertex_data[2].color.a,  sprite.vertex_data[2].uv.u, sprite.vertex_data[2].uv.v, // Bottom Left
	 sprite.vertex_data[3].position.x, sprite.vertex_data[3].position.y,  sprite.vertex_data[3].color.r, sprite.vertex_data[3].color.g, sprite.vertex_data[3].color.b, sprite.vertex_data[3].color.a,   sprite.vertex_data[3].uv.u, sprite.vertex_data[3].uv.v  // Top Left 
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::draw(leng::Sprite& sprite) {
    update_vertices(sprite);
    glBindTexture(GL_TEXTURE_2D, sprite.texture.id);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

} // namespace leng
