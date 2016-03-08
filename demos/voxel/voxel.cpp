#include <string>
#include <iostream>

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

const int BLOCKS = 10;

// Deltatime
float deltaTime = 0.0f;	 // Time between current frame and last frame
float lastFrame = 0.0f;  // Time of last frame

leng::Camera3D camera(glm::vec3(0.0f, 0.0f, -5.0f));

void handleEvents(leng::InputManager& inputManager) {
	if(inputManager.isPressed(SDLK_w))
	    camera.handleKeyboard(FORWARD, deltaTime);
	if(inputManager.isPressed(SDLK_s))
	    camera.handleKeyboard(BACKWARD, deltaTime);
	if(inputManager.isPressed(SDLK_a))
	    camera.handleKeyboard(LEFT, deltaTime);
	if(inputManager.isPressed(SDLK_d))
	    camera.handleKeyboard(RIGHT, deltaTime);
}

void renderBlock(glm::vec3 cubePositions[BLOCKS][BLOCKS][BLOCKS], GLuint containerVAO, GLint modelLoc) {
    glm::mat4 model;
    glBindVertexArray(containerVAO);
	for(int x = 0; x < BLOCKS; x++) {
	    for(int y = 0; y < BLOCKS; y++) {
		for(int z = 0; z < BLOCKS; z++) {
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
    window.setVsync(true);
    window.enableDepthTest();
    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);

    // Build and compile our shader program
    leng::Shader voxelShader("assets/shaders/voxel.vert", "assets/shaders/voxel.frag");
    
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

    glm::vec3 cubePositions[BLOCKS][BLOCKS][BLOCKS];

    GLuint VBO, voxelVAO;//, EBO;
    glGenVertexArrays(1, &voxelVAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(voxelVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable shader attributes
    voxelShader.enableAttribute("position", 3, 5, (GLvoid*)0);
    //shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    voxelShader.enableAttribute("texCoord", 2, 5, (GLvoid*)(3 * sizeof(GLfloat)));
    
    glBindVertexArray(0);

    GLuint sand_floor = leng::ResourceManager::getTexture("assets/textures/container.jpg").id;    
    leng::InputManager inputManager;

    float xOffset, yOffset;

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
		inputManager.setMouseCoords(float(event.motion.x), float(event.motion.y));
		// FPS Camera movement
		xOffset = SCREEN_WIDTH / 2 - event.motion.x;
		yOffset = SCREEN_HEIGHT / 2 - event.motion.y;
		camera.handleMouseMovement(xOffset, yOffset);
		break;
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		inputManager.handleKeyboardEvent(event);
		break;
	    case SDL_KEYDOWN:
		inputManager.handleKeyboardEvent(event);
		break;
	    case SDL_MOUSEBUTTONUP:
		inputManager.handleMouseEvent(event);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		inputManager.handleMouseEvent(event);
		break;
	    }
	}
	handleEvents(inputManager);

	SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// Rendering
        glClearColor(0.5f, 0.8f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sand_floor);
        glUniform1i(glGetUniformLocation(voxelShader.Program, "ourTexture"), 0);
        // Use cooresponding shader when setting uniforms/drawing objects
	voxelShader.use();

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(voxelShader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(voxelShader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(voxelShader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

 	renderBlock(cubePositions, voxelVAO, modelLoc);

	// Swap buffers
	window.swapWindow();
    }
    glDeleteVertexArrays(1, &voxelVAO);
    glDeleteBuffers(1, &VBO);
    
    return 0;
}
