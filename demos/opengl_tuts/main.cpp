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

float SCREEN_WIDTH = 1024.0f;
float SCREEN_HEIGHT = 768.0f;

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

int main() {
    leng::Window window("leng++", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.set_vsync(true);
    window.enable_depth_test();
    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);

        // Build and compile our shader program
    leng::Shader lighting_shader("assets/shaders/lighting.vert", "assets/shaders/lighting.frag");
    leng::Shader lamp_shader("assets/shaders/lamp.vert", "assets/shaders/lamp.frag");
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
    // Positions           // Normals           // Texture Coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

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

    // First, set the container's VAO (and VBO)
    GLuint VBO, containerVAO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);
    // Position attribute
    lighting_shader.enable_attribute("position", 3, 8, (GLvoid*)0);
    lighting_shader.enable_attribute("normal", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    lighting_shader.enable_attribute("texCoords", 2, 8, (GLvoid*)(6 * sizeof(GLfloat)));
    glBindVertexArray(0);

    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    lamp_shader.enable_attribute("position", 3, 8, (GLvoid*)0);
    glBindVertexArray(0);

    // Load textures
    GLuint diffuseMap, specularMap;
    glGenTextures(1, &diffuseMap);
    glGenTextures(1, &specularMap);
    int width, height;
    unsigned char* image;
    // Diffuse map
    image = SOIL_load_image("assets/textures/container2.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    // Specular map
    image = SOIL_load_image("assets/textures/container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, specularMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Set texture units
    lighting_shader.Use();
    glUniform1i(glGetUniformLocation(lighting_shader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lighting_shader.Program, "material.specular"), 1);
        
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
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
        // Use cooresponding shader when setting uniforms/drawing objects
        lighting_shader.Use();
	// Light position and view position for lighting calculations
	//GLint lightDirPos = glGetUniformLocation(lighting_shader.Program, "light.direction");
	GLint lightPosLoc = glGetUniformLocation(lighting_shader.Program, "light.position");
	GLint lightSpotdirLoc = glGetUniformLocation(lighting_shader.Program, "light.direction");
	GLint lightSpotCutOffLoc = glGetUniformLocation(lighting_shader.Program, "light.cutOff");
	GLint lightSpotOuterCutOffLoc = glGetUniformLocation(lighting_shader.Program, "light.outerCutOff");
	GLint viewPosLoc = glGetUniformLocation(lighting_shader.Program, "viewPos");
	//glUniform3f(lightDirPos, -0.2f, -1.0f, -0.3f);
	//glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	//glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(lightPosLoc,        camera.Position.x, camera.Position.y, camera.Position.z);	
	glUniform3f(lightSpotdirLoc,    camera.Front.x, camera.Front.y, camera.Front.z);
        glUniform1f(lightSpotCutOffLoc,      glm::cos(glm::radians(12.5f)));
        glUniform1f(lightSpotOuterCutOffLoc, glm::cos(glm::radians(17.5f)));
	
	// Set lights properties
        glUniform3f(glGetUniformLocation(lighting_shader.Program, "light.ambient"),  0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(lighting_shader.Program, "light.diffuse"),  0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lighting_shader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(lighting_shader.Program, "light.constant"),  1.0f);
        glUniform1f(glGetUniformLocation(lighting_shader.Program, "light.linear"),    0.09);
        glUniform1f(glGetUniformLocation(lighting_shader.Program, "light.quadratic"), 0.032);
	// Set material properties
        glUniform1f(glGetUniformLocation(lighting_shader.Program, "material.shininess"), 32.0f);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lighting_shader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(lighting_shader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(lighting_shader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
	// Bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

	// Draw the container (using container's vertex attributes)
        /*glBindVertexArray(containerVAO);
        glm::mat4 model;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);*/

	// Draw 10 containers with the same VAO and VBO information; only their world space coordinates differ
	glm::mat4 model;
        glBindVertexArray(containerVAO);
	for(GLuint i = 0; i < 10; i++) {
	    model = glm::mat4();
	    model = glm::translate(model, cubePositions[i]);
	    GLfloat angle = 20.0f * i; 
	    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
	    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	    glDrawArrays(GL_TRIANGLES, 0, 36);
	}
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
