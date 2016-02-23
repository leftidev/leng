#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "shader_program.h"

namespace leng {

class Renderer {
public:
    Renderer(leng::ShaderProgram& shader_program);
    ~Renderer();
    void create_vertex_array(leng::ShaderProgram& shader_program);
    void render();
    
private:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
};

}

#endif // RENDERER_H
