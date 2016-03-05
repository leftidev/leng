#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "shader.h"
#include "shader_program.h"
#include "input_manager.h"

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

// Deltatime
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;  	// Time of last frame

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
GLfloat cameraSpeed = 0.01f;


void handle_events(leng::InputManager& input_manager) {
	if(input_manager.is_pressed(SDLK_w))
	    cameraPos += cameraSpeed * deltaTime * cameraFront;
	if(input_manager.is_pressed(SDLK_s))
	    cameraPos -= cameraSpeed * deltaTime * cameraFront;
	if(input_manager.is_pressed(SDLK_a))
	    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
	if(input_manager.is_pressed(SDLK_d))
	    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;  
}

void load_shaders(std::vector<leng::Shader>& shaders, leng::ShaderProgram& shader_program) {
    // Create and compile the shaders
    shaders.push_back(leng::Shader("assets/shaders/pong.vert", GL_VERTEX_SHADER));
    shaders.push_back(leng::Shader("assets/shaders/pong.frag", GL_FRAGMENT_SHADER));
    // Link the shaders
    shader_program.link_shaders(shaders);
}

int main() {
    leng::Window window("leng++", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.set_vsync(true);
    window.enable_depth_test();

    // Hide cursor and trap mouse to window
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    std::vector<leng::Shader> shaders;
    leng::ShaderProgram shader_program;
    load_shaders(shaders, shader_program);

    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    /*
    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    */

    glm::vec3 cubePositions[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f), 
	glm::vec3( 2.0f,  5.0f, -15.0f), 
	glm::vec3(-1.5f, -2.2f, -2.5f),  
	glm::vec3(-3.8f, -2.0f, -12.3f),  
	glm::vec3( 2.4f, -0.4f, -3.5f),  
	glm::vec3(-1.7f,  3.0f, -7.5f),  
	glm::vec3( 1.3f, -2.0f, -2.5f),  
	glm::vec3( 1.5f,  2.0f, -2.5f), 
	glm::vec3( 1.5f,  0.2f, -1.5f), 
	glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    GLuint VBO, VAO;//, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable shader attributes
    shader_program.enable_attribute("position", 3, 5, (GLvoid*)0);
    //shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    shader_program.enable_attribute("text_coord", 2, 5, (GLvoid*)(3 * sizeof(GLfloat)));
    
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
    unsigned char* image = SOIL_load_image("assets/textures/container.jpg", &width, &height, 0, SOIL_LOAD_RGBA);

    // Create texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // De-allocate resources and unbind
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    leng::InputManager input_manager;

    bool running = true;
    SDL_Event event;
    while (running) {
	float currentFrame = SDL_GetTicks();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

	while(SDL_PollEvent(&event)) {
	    switch(event.type){
	    case SDL_QUIT:
		running = false;
		break;
	    case SDL_MOUSEMOTION:
		input_manager.set_mouse_coords(event);
		break;
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		input_manager.handle_keyboard_event(event);
		break;
	    case SDL_KEYDOWN:
		input_manager.handle_keyboard_event(event);
		break;
	    case SDL_MOUSEBUTTONUP:
		input_manager.handle_mouse_event(event);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		input_manager.handle_mouse_event(event);
		break;
	    }
	}
	handle_events(input_manager);

	// Rendering
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shader_program.program_id, "my_texture"), 0);
	
	shader_program.enable();

	// Camera/View transformation
        glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	
	glm::mat4 projection;
	projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
	
	GLuint model_loc = shader_program.get_uniform_location("model");
	GLuint view_loc = shader_program.get_uniform_location("view");
	GLuint proj_loc = shader_program.get_uniform_location("projection");
	
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draw container
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	for(GLuint i = 0; i < 10; i++) {
		glm::mat4 model;
		model = glm::translate(model, cubePositions[i]);
		GLfloat angle = glm::radians(20.0f * i); 
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	    }
	glBindVertexArray(0);

	shader_program.disable();
	// Swap buffers
	window.swap_window();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    return 0;
}
