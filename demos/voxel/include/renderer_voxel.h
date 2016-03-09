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

class RendererVoxel {
public:
    RendererVoxel();
    ~RendererVoxel();
    void initVAO();
    void draw(leng::Block*** blocks, leng::Camera3D& camera);
    GLuint VBO;
    GLuint VAO;
    GLint modelLoc;
    GLint viewLoc;
    GLint projLoc;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 model;
    leng::Shader voxelShader {"assets/shaders/voxel.vert", "assets/shaders/voxel.frag"};

    //std::vector<Mesh> meshList;
};

}

#endif // RENDERER_2D_H
