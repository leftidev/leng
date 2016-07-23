#include "sprite_font.h"

namespace leng {
SpriteFont::SpriteFont(float x, float y, float Size, const char* fontPath, const char* text) {
    position.x = x;
    position.y = y;
    size = Size;

    // load font.ttf at size 16 into fonts
    font = TTF_OpenFont(fontPath, size);
    if(!font) {
	printf("TTF_OpenFont error: %s\n", TTF_GetError());
	// handle error
    }
    
    SDL_Color color = {255, 255, 255, 255};
    surface = TTF_RenderUTF8_Blended(font, text, color);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    // Top right
    vertexData2[0].setPosition(position.x + surface->w, position.y + surface->h);
    vertexData2[0].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData2[0].setUV(1.0f, 1.0f);
    // Bottom right
    vertexData2[1].setPosition(position.x + surface->w, position.y);
    vertexData2[1].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData2[1].setUV(1.0f, 0.0f);
    // Bottom left
    vertexData2[2].setPosition(position.x, position.y);
    vertexData2[2].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData2[2].setUV(0.0f, 0.0f);
    // Top left
    vertexData2[3].setPosition(position.x, position.y + surface->h);
    vertexData2[3].setColor(1.0f, 1.0f, 1.0f, 1.0f);
    vertexData2[3].setUV(0.0f, 1.0f);
}
    
SpriteFont::~SpriteFont() {
    SDL_FreeSurface(surface);
    // free the font
    TTF_CloseFont(font);
    font = NULL;    
}

void SpriteFont::update(glm::vec2 Position) {
    position = Position;

    // Update sprite font
    vertexData2[0].setPosition(position.x + surface->w, position.y + surface->h);
    vertexData2[1].setPosition(position.x + surface->w, position.y);
    vertexData2[2].setPosition(position.x, position.y);
    vertexData2[3].setPosition(position.x, position.y + surface->h);
}

void SpriteFont::update(glm::vec2 Position, const char* text) {
    position = Position;

    // Update sprite font
    vertexData2[0].setPosition(position.x + surface->w, position.y + surface->h);
    vertexData2[1].setPosition(position.x + surface->w, position.y);
    vertexData2[2].setPosition(position.x, position.y);
    vertexData2[3].setPosition(position.x, position.y + surface->h);

    SDL_Color color = {255, 255, 255, 255};
    surface = TTF_RenderUTF8_Blended(font, text, color);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    }
    
} // namespace leng
