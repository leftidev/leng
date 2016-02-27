#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "shader.h"
#include "shader_program.h"
#include "camera_2d.h"
#include "renderer.h"
#include "texture.h"
#include "sprite.h"

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    leng::Renderer renderer(shader_program);
    /*
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // Positions          // Colors           // Texture Coords
         100.5f,  100.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         100.5f, -100.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -100.5f, -100.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -100.5f,  100.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
    };
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable shader attributes
    shader_program.enable_attribute("position", 3, 8, (GLvoid*)0);
    shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    shader_program.enable_attribute("text_coord", 2, 8, (GLvoid*)(6 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
    */
    /*
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
    */
    //leng::Texture texture("assets/textures/awesomeface.png");
    leng::Sprite sprite(0, 0, 100, 100, "assets/textures/awesomeface.png");
    leng::Sprite sprite2(-300, 0, 300, 100, "assets/textures/awesomeface.png");
    // Set up the camera
    leng::Camera2D camera;
    camera.init(800, 600);
    
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
	camera.update();
	// Rendering
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(glGetUniformLocation(shader_program.program_id, "my_texture"), 0);
	
	shader_program.enable();

	// Grab the camera matrix
	glm::mat4 proj_mat = camera.get_camera_matrix();
	GLuint camera_loc = shader_program.get_uniform_location("transform");
	glUniformMatrix4fv(camera_loc, 1, GL_FALSE, glm::value_ptr(proj_mat));
	
        // Draw container
	/*
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
	*/
	renderer.draw(sprite);
	renderer.draw(sprite2);	
	shader_program.disable();
	// Swap buffers
	window.swap_window();
    }
    
    return 0;
}
