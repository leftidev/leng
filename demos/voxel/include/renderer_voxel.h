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
};
    
class RendererVoxel {
public:
    RendererVoxel();
    ~RendererVoxel();

    void createMesh();
    void addVertexToMesh(int meshID, Vertex2 vert);
    void finishMesh();
    void renderMesh(leng::Camera3D& camera, int numVertices);

    GLuint VBO;
    GLuint VAO;
    GLint modelLoc;
    GLint viewLoc;
    GLint projLoc;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    leng::Shader voxelShader {"assets/shaders/voxel.vert", "assets/shaders/voxel.frag"};

    std::vector<Mesh> meshes;
};

}

#endif // RENDERER_2D_H
