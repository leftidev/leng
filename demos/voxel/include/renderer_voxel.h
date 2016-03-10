#ifndef RENDERER_VOXEL_H
#define RENDERER_VOXEL_H

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "camera_3d.h"
#include "block.h"
#include "vertex2.h"

namespace leng {

struct Mesh {
    std::vector<Vertex2> vertexData;
    GLuint VBO;
};
    
class RendererVoxel {
public:
    RendererVoxel();
    ~RendererVoxel();

    void createMesh();
    void addVertexToMesh(int meshID, Vertex2 vert);
    void finishMesh(int meshID, leng::Shader& voxelShader);
    void renderMesh(int numVertices, leng::Shader& shader, const glm::vec3& pos);

    GLuint VAO;
    GLint modelLoc;
    GLint viewLoc;
    GLint projLoc;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    

    std::vector<Mesh> meshes;
};

}

#endif // RENDERER_2D_H
