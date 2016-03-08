#ifndef RENDERER_3D_H
#define RENDERER_3D_H

#include <GL/glew.h>

#include "shader.h"
#include "camera_3d.h"
#include "block.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace leng {

class Renderer3D {
public:
    Renderer3D();
    ~Renderer3D();
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
};

}

#endif // RENDERER_2D_H
