#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>

namespace leng {

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);    
    void use();
    void enableAttribute(const std::string& attrName, int count, int stride, void* ptr);
    GLuint getUniformLocation(const std::string& uniformName);

    GLuint Program;
};

} // namespace leng

#endif // SHADER_H

