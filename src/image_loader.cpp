#include "image_loader.h"

#include <SOIL/SOIL.h>

namespace leng {
    
Texture ImageLoader::loadImage(std::string path) {
    Texture texture = {};
    // Generate and bind texture
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    // Load, and generate mipmaps
    const char* c = path.c_str();
    unsigned char* image = SOIL_load_image(c, &width, &height, 0, SOIL_LOAD_RGBA);

    // Create texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    texture.width = width;
    texture.height = height;
    
    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // De-allocate resources and unbind
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
    
} // namespace leng
