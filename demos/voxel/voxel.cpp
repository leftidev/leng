#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "input_manager.h"
#include "camera_3d.h"
#include "shader.h"
#include "resource_manager.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float SCREEN_WIDTH = 1024.0f;
float SCREEN_HEIGHT = 768.0f;

// Deltatime
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;  	// Time of last frame

leng::Camera3D camera(glm::vec3(0.0f, 0.0f, 3.0f));

void handle_events(leng::InputManager& input_manager) {
	if(input_manager.is_pressed(SDLK_w))
	    camera.handle_keyboard(FORWARD, deltaTime);
	if(input_manager.is_pressed(SDLK_s))
	    camera.handle_keyboard(BACKWARD, deltaTime);
	if(input_manager.is_pressed(SDLK_a))
	    camera.handle_keyboard(LEFT, deltaTime);
	if(input_manager.is_pressed(SDLK_d))
	    camera.handle_keyboard(RIGHT, deltaTime);
}

void render_block(glm::vec3 cubePositions[10][10][10], GLuint containerVAO, GLint modelLoc) {
    glm::mat4 model;
    glBindVertexArray(containerVAO);
	for(int x = 0; x < 10; x++) {
	    for(int y = 0; y < 10; y++) {
		for(int z = 0; z < 10; z++) {
		    model = glm::mat4();
		    model = glm::translate(model, glm::vec3(x, y, z));
		    //GLfloat angle = 20.0f * i; 
		    //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		    glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	    }
	}
   glBindVertexArray(0);   
}

int main() {
    leng::Window window("leng++", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.set_vsync(true);
    window.enable_depth_test();
    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);

    // Build and compile our shader program
    leng::Shader voxel_shader("assets/shaders/voxel.vert", "assets/shaders/voxel.frag");
    
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

    glm::vec3 cubePositions[10][10][10];

    // Set voxel VAO
    GLuint VBO, voxelVAO;
    glGenVertexArrays(1, &voxelVAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(voxelVAO);
    
    // Set VBO and upload vertex data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set the vertex attributes
    voxel_shader.enable_attribute("position", 3, 5, (GLvoid*)0);
    voxel_shader.enable_attribute("texCoord", 2, 5, (GLvoid*)3);

    glBindVertexArray(0);

    // Load textures
    leng::ResourceManager resource_manager;
    //leng::Texture sand_floor = resource_manager.load_texture("assets/textures/sand.jpg");
    GLuint sand_floor = leng::ResourceManager::getTexture("assets/textures/container.jpg").id;    
    leng::InputManager input_manager;

    float x_offset, y_offset;

    SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
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
		input_manager.set_mouse_coords(float(event.motion.x), float(event.motion.y));
		// FPS Camera movement
		x_offset = SCREEN_WIDTH / 2 - event.motion.x;
		y_offset = SCREEN_HEIGHT / 2 - event.motion.y;
		camera.handle_mouse_movement(x_offset, y_offset);
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

	SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// Rendering
        glClearColor(0.5f, 0.8f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sand_floor);
        glUniform1i(glGetUniformLocation(voxel_shader.Program, "ourTexture"), 0);
        // Use cooresponding shader when setting uniforms/drawing objects
	voxel_shader.Use();

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(voxel_shader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(voxel_shader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(voxel_shader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sand_floor);

 	render_block(cubePositions, voxelVAO, modelLoc);

	// Swap buffers
	window.swap_window();
    }
    glDeleteVertexArrays(1, &voxelVAO);
    glDeleteBuffers(1, &VBO);
    
    return 0;
}
