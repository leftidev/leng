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
    void Use();
    void enable_attribute(const std::string& attr_name, int count, int stride, void* ptr);
    GLuint get_uniform_location(const std::string& uniformName);

    GLuint Program;
};

} // namespace leng

#endif // SHADER_H

