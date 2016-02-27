#include "texture.h"

namespace leng {

Texture::Texture(const char* path) {
    // Generate and bind texture
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    // Load, and generate mipmaps
    unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);

    // Create texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // De-allocate resources and unbind
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}
    
Texture::~Texture() { }

} // namespace leng
