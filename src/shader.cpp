#include "shader.h"

#include <iostream>
#include <vector>
#include <fstream>

namespace leng {

Shader::Shader(const std::string& path, GLenum shader_type) {
    shader_id = glCreateShader(shader_type);
    if(shader_id == 0) {
	std::cout << "glCreateShader failed" << std::endl;
    }
    // Open the file
    std::ifstream shader_file(path);
    if(shader_file.fail()) {
	perror(path.c_str());
	std::cout << "Failed to open " + path << std::endl;
    }
    // Store all the text in the file
    std::string file_contents = "";
    // Grab each line of the file
    std::string line;
    // Get all lines in the file and add it to file_contents
    while(std::getline(shader_file, line)) {
	file_contents += line + "\n";
    }

    shader_file.close();

    // Get a pointer to file_contents c string
    const char* contents_ptr = file_contents.c_str();

    glShaderSource(shader_id, 1, &contents_ptr, nullptr);
    glCompileShader(shader_id);

    // Error checking
    GLint success = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
	GLint max_length = 0;
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);

	// The maxLength includes the NULL character
	std::vector<char> error_log(max_length);
	glGetShaderInfoLog(shader_id, max_length, &max_length, &error_log[0]);

	// Exit with failure
	glDeleteShader(shader_id);

	// Print error log and quit
	std::printf("%s\n", &(error_log[0]));
	std::cout << "Shader " + path + " failed to compile!" << std::endl;
    }
}

Shader::~Shader() {}

} // namespace leng
