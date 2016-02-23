#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>
#include "shader.h"

namespace leng {

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    void link_shaders(const std::vector<Shader>& shaders);
    void enable_attribute(const std::string& attr_name, int count, int stride, void* ptr);
    GLuint get_uniform_location(const std::string& uniformName);
    //void set_mat4(GLuint shader_program, const char* name, mat4 val);
    void enable();
    void disable();
    
    GLuint program_id;
};
    
} // namespace leng

#endif // SHADER_PROGRAM_H
