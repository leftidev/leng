#ifndef SPRITE_FONT_H
#define SPRITE_FONT_H

#include "SDL2/SDL_ttf.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "vertex.h"

namespace leng {

class SpriteFont {
public:
    SpriteFont(float x, float y, float Size, const char* fontPath, const char* text);
    ~SpriteFont();
    void update(glm::vec2 Position);
    
    float size;
    Vertex3 vertexData2[4];
    GLuint texture;
    TTF_Font *font;
    glm::vec2 position;
    SDL_Surface *surface;
};

} // namespace leng

#endif // SPRITE_FONT_H
