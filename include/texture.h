#ifndef TEXTURE_H
#define TEXTURE_H

#include <SOIL/SOIL.h>
#include <GL/glew.h>

namespace leng {

struct Texture {
    Texture();
    ~Texture();
    void init(const char* path);
    GLuint id;
};
    
} // namespace leng

#endif // TEXTURE_H
