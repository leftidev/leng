#include "renderer_3d.h"
#include "chunk.h"
#include <iostream>

namespace leng {
    
RendererVoxel::RendererVoxel() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

RendererVoxel::~RendererVoxel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
   
void RendererVoxel::createMesh() {
    // TODO: Create VBO per mesh
    Mesh mesh;
    meshes.push_back(mesh);
}
    
void RendererVoxel::addVertexToMesh(int meshID, Vertex2 vert) {	
    meshes.at(meshID).vertexData.push_back(vert);
}

void RendererVoxel::finishMesh() {
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, meshes.at(0).vertexData.size() * sizeof(Vertex2), &meshes.at(0).vertexData[0], GL_STATIC_DRAW);
    // Enable shader attributes
    voxelShader.enableAttribute("position", 3, 5, (GLvoid*)0);
    //shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    voxelShader.enableAttribute("texCoord", 2, 5, (GLvoid*)(3 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

void RendererVoxel::renderMesh(leng::Camera3D& camera, int numVertices) {
    glUniform1i(glGetUniformLocation(voxelShader.Program, "ourTexture"), 0);
    // Use cooresponding shader when setting uniforms/drawing objects
    voxelShader.use();

    model = glm::mat4();
    // Create camera transformations
    view = camera.GetViewMatrix();
    projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
    // Get the uniform locations
    modelLoc = glGetUniformLocation(voxelShader.Program, "model");
    viewLoc  = glGetUniformLocation(voxelShader.Program,  "view");
    projLoc  = glGetUniformLocation(voxelShader.Program,  "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Render blocks
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);

    // Number of vertices rendered
    std::cout << numVertices << std::endl;
}

} // namespace leng


