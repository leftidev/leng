#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "shader_program.h"
#include "sprite.h"

namespace leng {

class Renderer {
public:
    Renderer();
    ~Renderer();
    void init_vao(leng::ShaderProgram& shader_program);
    void update_vertices(leng::Sprite& sprite);
    void draw(leng::Sprite& sprite);
    
private:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint indices[6];
};

}

#endif // RENDERER_H
