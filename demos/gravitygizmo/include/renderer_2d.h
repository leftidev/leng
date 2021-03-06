#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <GL/glew.h>

#include "shader.h"
#include "sprite.h"
#include "sprite_font.h"

namespace leng {

class Renderer2D {
public:
    Renderer2D();
    ~Renderer2D();
    void initVAO();
    void updateVertices(leng::Sprite& sprite);
    void updateVertices(leng::SpriteFont& spriteFont);
    void draw(leng::Sprite& sprite);
    void drawText(leng::SpriteFont& spriteFont);    
private:
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;
    GLuint indices[6];
};

}

#endif // RENDERER_2D_H
