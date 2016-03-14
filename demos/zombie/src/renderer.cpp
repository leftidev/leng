#include "renderer.h"

namespace leng {
    
Renderer::Renderer() {
    glGenVertexArrays(1, &lightingVAO);
    glGenVertexArrays(1, &lampVAO);
    glGenVertexArrays(1, &tilesVAO);
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &lampVBO);
    glGenBuffers(1, &EBO);
    
    // EBO indices for a quad
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 3;
    indices[3] = 1;
    indices[4] = 2;
    indices[5] = 3;
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &lightingVAO);
    glDeleteVertexArrays(1, &lampVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
    
void Renderer::initLightVAO(leng::Shader& shader) {
    glBindVertexArray(lightingVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Enable shader attributes
    shader.enableAttribute("position", 2, 7, (GLvoid*)0);
    shader.enableAttribute("normal", 3, 7, (GLvoid*)(2 * sizeof(GLfloat)));
    shader.enableAttribute("texCoords", 2, 7, (GLvoid*)(5 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

void Renderer::initLampVAO(leng::Shader& shader) {
    GLfloat vertices[] = {
        // Positions
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f
    };

    glBindVertexArray(lampVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lampVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Enable shader attributes
    shader.enableAttribute("position", 3, 3, (GLvoid*)0);
    
    glBindVertexArray(0);
}
    
void Renderer::updateVertices(leng::Sprite& sprite) {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sprite.vertexData), sprite.vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::setSpriteAngle(leng::Sprite& sprite, float angle) {
    sprite.setAngle(angle);	
}

void Renderer::draw(leng::Sprite& sprite, leng::Shader& shader, float angle) {
    updateVertices(sprite);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite.textureID);
    modelLoc = glGetUniformLocation(shader.Program, "model");
    // Render chunk
    glBindVertexArray(lightingVAO);
    
    model = glm::mat4();
    //model = glm::translate(model, position);
    //GLfloat Angle = -90.0f; 
    //model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);

    // Number of vertices rendered
    //std::cout << numVertices << std::endl;
}

void Renderer::drawLamp(glm::vec3 position, leng::Shader& shader) {
    //updateVertices(sprite);
    
    modelLoc = glGetUniformLocation(shader.Program, "model");
    // Render chunk
    glBindVertexArray(lampVAO);
    
    model = glm::mat4();
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(10.0f)); // Make it a bigger cube
    //GLfloat angle = 20.0f * 3.5f; 
    //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);

    // Number of vertices rendered
    //std::cout << numVertices << std::endl;
}

void Renderer::createMesh() {
    // TODO: Create VBO per mesh
    Mesh mesh;
    glGenBuffers(1, &mesh.VBO);
    meshes.push_back(mesh);
}
    
void Renderer::addVertexToMesh(int meshID, Vertex2 vert) {	
    meshes.at(meshID).vertexData.emplace_back(vert);
}

void Renderer::finishMesh(int meshID, leng::Shader& shader) {
    glBindVertexArray(tilesVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, meshes.at(meshID).VBO);
    //glBufferData(GL_ARRAY_BUFFER, meshes.at(meshID).vertexData.size() * sizeof(Vertex2), &meshes.at(meshID).vertexData[0], GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, meshes.at(meshID).vertexData.size() * sizeof(Vertex2), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, meshes.at(meshID).vertexData.size() * sizeof(Vertex2), meshes.at(meshID).vertexData.data());

    // Enable shader attributes
    shader.enableAttribute("position", 2, 7, (GLvoid*)0);
    shader.enableAttribute("normal", 3, 7, (GLvoid*)(2 * sizeof(GLfloat)));
    shader.enableAttribute("texCoords", 2, 7, (GLvoid*)(5 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

    void Renderer::renderMesh(int numVertices, leng::Shader& shader, const glm::vec3& position) {
    modelLoc = glGetUniformLocation(shader.Program, "model");
    // Render chunk
    glBindVertexArray(tilesVAO);
    
    model = glm::mat4();
    model = glm::translate(model, position);
    //GLfloat angle = 20.0f * 3.5f; 
    //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    
    glBindVertexArray(0);

    // Number of vertices rendered
    //std::cout << numVertices << std::endl;
}

    
} // namespace leng
