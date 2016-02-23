#include <iostream>

#include "shader_program.h"

namespace leng {
    
ShaderProgram::ShaderProgram() {
    program_id = glCreateProgram(); 
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_id);
}

void ShaderProgram::link_shaders(const std::vector<Shader>& shaders) {
    // Attach all shaders
    for (unsigned i = 0; i < shaders.size(); ++i) {
	glAttachShader(program_id, shaders[i].shader_id);
    }

    // Link the program
    glLinkProgram(program_id);

    // Detach all shaders
    for (unsigned i = 0; i < shaders.size(); ++i) {
	glDetachShader(program_id, shaders[i].shader_id);
    }

    // Error checking
    GLint is_linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, (int *)&is_linked);
    if (is_linked == GL_FALSE) {
	GLint max_length = 0;
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);

	// The maxLength includes the NULL character
	std::vector<char> error_log(max_length);
	glGetProgramInfoLog(program_id, max_length, &max_length, &error_log[0]);

	for (unsigned i = 0; i < shaders.size(); ++i) {
	    glDeleteShader(shaders[i].shader_id);
	}

	glDeleteProgram(program_id);

	// Print the error log and quit.
	std::printf("%s\n", &(error_log[0]));
	std::cout << "Shaders failed to link!" << std::endl;
    }
}

GLuint ShaderProgram::get_uniform_location(const std::string& uniformName) {
    GLuint uniform = glGetUniformLocation(program_id, uniformName.c_str());
    if (uniform == GL_INVALID_INDEX) {
	std::cout << "Uniform " + uniformName + " not found in shader!" << std::endl;
    }
    return uniform;
}

// Enable the shader and all its attributes
void ShaderProgram::enable() {
    glUseProgram(program_id);
}

// Disable the shader
void ShaderProgram::disable() {
    glUseProgram(0);
}

void ShaderProgram::enable_attribute(const std::string& attr_name, int count, int stride, void* ptr) {
    GLint attr = glGetAttribLocation(program_id, attr_name.c_str());
    if (attr == -1) {
	std::cout << "Shader has no attribute called " + attr_name << std::endl;
    } else {
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, count, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * stride, ptr);
    }   
}
/*
void ShaderProgram::set_mat4(GLuint shader_program, const std::string& name, mat4 val) {
  GLint location = glGetUniformLocation(shader_program, name);
  if (location == -1) {
      fprintf(stderr, "Shader has no uniform mat4 called '%s'", name.c_str());
  } else {
    glUniformMatrix4fv(location, 1, GL_TRUE, (float*)&val);
  }
}
*/

} // namespace leng
