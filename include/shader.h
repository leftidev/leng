#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

namespace leng {

class Shader {
public:
    Shader(const std::string& path, GLenum shader_type);
    ~Shader();
	
private:
    GLuint shader_id;
};
    
} // namespace leng

#endif // SHADER_H
