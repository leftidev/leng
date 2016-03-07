#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "input_manager.h"
#include "camera_3d.h"
#include "shader.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float SCREEN_WIDTH = 800.0f;
float SCREEN_HEIGHT = 600.0f;

// Deltatime
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;  	// Time of last frame

leng::Camera3D camera(glm::vec3(0.0f, 0.0f, 3.0f));

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

/*
void mouse_movement(float x, float y)
{
    GLfloat xoffset = -x;
    GLfloat yoffset = y; // Reversed since y-coordinates go from bottom to left

    GLfloat sensitivity = 0.1;  // Change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}  
*/
int main() {
    leng::Window window("leng++", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.set_vsync(true);
    window.enable_depth_test();

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);

        // Build and compile our shader program
    leng::Shader lighting_shader("assets/shaders/lighting.vert", "assets/shaders/lighting.frag");
    leng::Shader lamp_shader("assets/shaders/lamp.vert", "assets/shaders/lamp.frag");
    
    // Set up vertex data (and buffer(s)) and attribute pointers
   GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, containerVAO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);
    // Position attribute
    lamp_shader.enable_attribute("position", 3, 3, (GLvoid*)0);
    glBindVertexArray(0);

    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    lighting_shader.enable_attribute("position", 3, 3, (GLvoid*)0);
    glBindVertexArray(0);

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
        //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
        // Use cooresponding shader when setting uniforms/drawing objects
        lighting_shader.Use();
        GLint objectColorLoc = glGetUniformLocation(lighting_shader.Program, "objectColor");
        GLint lightColorLoc  = glGetUniformLocation(lighting_shader.Program, "lightColor");
        glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
        glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lighting_shader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(lighting_shader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(lighting_shader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the container (using container's vertex attributes)
        glBindVertexArray(containerVAO);
        glm::mat4 model;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lamp_shader.Use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lamp_shader.Program, "model");
        viewLoc  = glGetUniformLocation(lamp_shader.Program, "view");
        projLoc  = glGetUniformLocation(lamp_shader.Program, "projection");
        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
	// Swap buffers
	window.swap_window();
    }
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    
    return 0;
}
