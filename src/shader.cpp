#include "shader.h"

namespace leng {
    
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // 1. Retrieve the vertex/fragment source code from filePath
    // Open the file
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);
    if(vertexFile.fail()) {
	perror(vertexPath.c_str());
	std::cout << "Failed to open " + vertexPath << std::endl;
    }
    if(fragmentFile.fail()) {
	perror(fragmentPath.c_str());
	std::cout << "Failed to open " + fragmentPath << std::endl;
    }

    // Store all the text in the file
    std::string vertexFileContents = "";
    std::string fragmentFileContents = "";

    // Grab each line of the file
    std::string vertexLine;
    std::string fragmentLine;

    // Get all lines in the file and add it to file_contents
    while(std::getline(vertexFile, vertexLine)) {
	vertexFileContents += vertexLine + "\n";
    }
    while(std::getline(fragmentFile, fragmentLine)) {
	fragmentFileContents += fragmentLine + "\n";
    }

    vertexFile.close();
    fragmentFile.close();

    const char* vShaderCode = vertexFileContents.c_str();
    const char * fShaderCode = fragmentFileContents.c_str();
    // 2. Compile shaders
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}
    
// Uses the current shader
void Shader::use() { 
    glUseProgram(this->Program); 
}
    
void Shader::enableAttribute(const std::string& attrName, int count, int stride, void* ptr) {
    GLint attr = glGetAttribLocation(this->Program, attrName.c_str());
    if (attr == -1) {
	std::cout << "Shader has no attribute called " + attrName << std::endl;
    } else {
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, count, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * stride, ptr);
    }   
}

GLuint Shader::getUniformLocation(const std::string& uniformName) {
    GLuint uniform = glGetUniformLocation(this->Program, uniformName.c_str());
    if (uniform == GL_INVALID_INDEX) {
	std::cout << "Uniform " + uniformName + " not found in shader!" << std::endl;
    }
    return uniform;
}

} // namespace leng
