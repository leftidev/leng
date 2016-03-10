#include "renderer_3d.h"
#include "chunk.h"
#include <iostream>

namespace leng {
    
RendererVoxel::RendererVoxel() {
    glGenVertexArrays(1, &VAO);

}

RendererVoxel::~RendererVoxel() {
    glDeleteVertexArrays(1, &VAO);
    
    for(unsigned int i = 0; i < meshes.size(); i++) {
	glDeleteBuffers(1, &meshes[i].VBO);
    }
}
   
void RendererVoxel::createMesh() {
    // TODO: Create VBO per mesh
    Mesh mesh;
    glGenBuffers(1, &mesh.VBO);
    meshes.push_back(mesh);
}
    
void RendererVoxel::addVertexToMesh(int meshID, Vertex2 vert) {	
    meshes.at(meshID).vertexData.emplace_back(vert);
}

void RendererVoxel::finishMesh(int meshID, leng::Shader& voxelShader) {
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, meshes.at(meshID).VBO);
    //glBufferData(GL_ARRAY_BUFFER, meshes.at(meshID).vertexData.size() * sizeof(Vertex2), &meshes.at(meshID).vertexData[0], GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, meshes.at(meshID).vertexData.size() * sizeof(Vertex2), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, meshes.at(meshID).vertexData.size() * sizeof(Vertex2), meshes.at(meshID).vertexData.data());

    // Enable shader attributes
    voxelShader.enableAttribute("position", 3, 5, (GLvoid*)0);
    //shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    voxelShader.enableAttribute("texCoord", 2, 5, (GLvoid*)(3 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

    void RendererVoxel::renderMesh(int numVertices, leng::Shader& shader, const glm::vec3& position) {
    modelLoc = glGetUniformLocation(shader.Program, "model");
    // Render chunk
    glBindVertexArray(VAO);
    
    model = glm::mat4();
    model = glm::translate(model, position);
    //GLfloat angle = 20.0f * 3.5f; 
    //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    
    glBindVertexArray(0);

    // Number of vertices rendered
    std::cout << numVertices << std::endl;
}

} // namespace leng


