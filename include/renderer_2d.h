#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <GL/glew.h>

#include "shader.h"
//#include "sprite.h"

namespace leng {

class Renderer2D {
public:
    Renderer2D();
    ~Renderer2D();
    void initVAO(leng::Shader& shader);
    //  void updateVertices(leng::Sprite& sprite);
    //void draw(leng::Sprite& sprite);
    
private:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint indices[6];
};

}

#endif // RENDERER_2D_H
