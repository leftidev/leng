#ifndef RENDERER_H
#define RENDERER_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "sprite.h"

namespace leng {

class Renderer {
public:
    Renderer();
    ~Renderer();
    void initLightVAO(leng::Shader& shader);
    void initLampVAO(leng::Shader& shader);
    void updateVertices(leng::Sprite& sprite);
    void draw(leng::Sprite& sprite, leng::Shader& shader);
    void drawLamp(glm::vec3 position, leng::Shader& shader);
    
private:
    GLuint VBO, lampVBO;
    GLuint lightingVAO;
    GLuint lampVAO;
    GLuint EBO;
    GLuint indices[6];
    glm::mat4 model;
    GLint modelLoc;
};

}

#endif // RENDERER_H
