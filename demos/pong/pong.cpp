#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "shader.h"
#include "shader_program.h"


void load_shaders(std::vector<leng::Shader>& shaders, leng::ShaderProgram& shader_program) {
    // Create and compile the shaders
    shaders.push_back(leng::Shader("assets/shaders/pong.vert", GL_VERTEX_SHADER));
    shaders.push_back(leng::Shader("assets/shaders/pong.frag", GL_FRAGMENT_SHADER));
    // Link the shaders
    shader_program.link_shaders(shaders);
}

int main() {
    leng::Window window("leng++", 800, 600);
    window.set_vsync(true);

    std::vector<leng::Shader> shaders;
    leng::ShaderProgram shader_program;
    load_shaders(shaders, shader_program);

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO); // We can generate multiple VAOs or buffers at same time
    glGenBuffers(1, &VBO);  

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Enable shader attributes
    shader_program.enable_attribute("position", 3, 9, (GLvoid*)0);
    shader_program.enable_attribute("color", 4, 9, (GLvoid*)(3 * sizeof(GLfloat)));
    shader_program.enable_attribute("text_coord", 2, 9, (GLvoid*)(7 * sizeof(GLfloat)));
    
    glBindVertexArray(0);

    GLuint texture;
    // Generate and bind texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height;
    // Load, and generate mipmaps
    unsigned char* image = SOIL_load_image("assets/textures/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGBA);

    // Create texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // De-allocate resources and unbind
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    bool running = true;
    SDL_Event event;
    while (running) {
	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		break;
	    case SDL_QUIT:
		running = false;
		break;
	    }
	}
	// Rendering
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader_program.enable();
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	GLfloat vertices[] = {
	    // First triangle
	    0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // Top Right
	    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // Top Left
	    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
	    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// Bottom Left
	    0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Bottom Right
	    0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f// Top Right
	}; 

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shader_program.disable();
	// Swap buffers
	window.swap_window();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    return 0;
}
