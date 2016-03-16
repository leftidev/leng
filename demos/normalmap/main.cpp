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
glm::vec3 lightPos(0.0f, 0.0f, 2.0f);

bool normalMapping = true;

void handleEvents(leng::InputManager& inputManager) {
	if(inputManager.isPressed(SDLK_w))
	    camera.handleKeyboard(FORWARD, deltaTime);
	if(inputManager.isPressed(SDLK_s))
	    camera.handleKeyboard(BACKWARD, deltaTime);
	if(inputManager.isPressed(SDLK_a))
	    camera.handleKeyboard(LEFT, deltaTime);
	if(inputManager.isPressed(SDLK_d))
	    camera.handleKeyboard(RIGHT, deltaTime);

	if(inputManager.isPressed(SDLK_UP))
	    camera.handleKeyboard(UP, deltaTime);
	if(inputManager.isPressed(SDLK_DOWN))
	    camera.handleKeyboard(DOWN, deltaTime);
	if(inputManager.isPressed(SDLK_LEFT))
	    camera.handleKeyboard(LEFT, deltaTime);
	if(inputManager.isPressed(SDLK_RIGHT))
	    camera.handleKeyboard(RIGHT, deltaTime);
	if(inputManager.isPressed(SDLK_u))
	    normalMapping = true;
	if(inputManager.isPressed(SDLK_j))
	    normalMapping = false;
}

int main() {
    leng::Window window("OpenGL Tuts", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.setVsync(true);
    window.enableDepthTest();
    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_ShowCursor(SDL_DISABLE);

        // Build and compile our shader program
    leng::Shader lightingShader("assets/shaders/lighting.vert", "assets/shaders/lighting.frag");
    leng::Shader lampShader("assets/shaders/lamp.vert", "assets/shaders/lamp.frag");
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
    // Positions           // Normals           // Texture Coords
    -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f
    };

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f)
    };

    glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.0f,  0.0f,  1.0f),
	//glm::vec3( 2.3f, -3.3f, -4.0f),
	//glm::vec3(-4.0f,  2.0f, -12.0f),
	//glm::vec3( 0.0f,  0.0f, -3.0f)
};
    
    // First, set the container's VAO (and VBO)
    GLuint VBO, containerVAO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);
    // Position attribute
    lightingShader.enableAttribute("position", 2, 7, (GLvoid*)0);
    lightingShader.enableAttribute("normal", 3, 7, (GLvoid*)(2 * sizeof(GLfloat)));
    lightingShader.enableAttribute("texCoords", 2, 7, (GLvoid*)(5 * sizeof(GLfloat)));
    glBindVertexArray(0);

    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    lampShader.enableAttribute("position", 2, 7, (GLvoid*)0);
    glBindVertexArray(0);

    // Load textures
    GLuint diffuseMap, specularMap;
    glGenTextures(1, &diffuseMap);
    glGenTextures(1, &specularMap);
    int width, height;
    unsigned char* image;
    // Diffuse map
    image = SOIL_load_image("assets/textures/brickwall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    // Specular map
    image = SOIL_load_image("assets/textures/brickwall_normal.jpg", &width, &height, 0, SOIL_LOAD_RGB);
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
    lightingShader.use();
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(lightingShader.Program, "material.normalMap"), 1);
        
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
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "normalMapping"), normalMapping);
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
        // Point light 1
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(lightingShader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(lightingShader.Program,  "projection");
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
	model = glm::mat4();
	model = glm::translate(model, cubePositions[0]);
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 1.0f)); // Make it a smaller cube
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc  = glGetUniformLocation(lampShader.Program, "view");
        projLoc  = glGetUniformLocation(lampShader.Program, "projection");
        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        model = glm::mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray(lightVAO);
         for (GLuint i = 0; i < 4; i++)
        {
            model = glm::mat4();
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        glBindVertexArray(0);
	// Swap buffers
	window.swapWindow();
    }
    glDeleteVertexArrays(1, &containerVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
    
    return 0;
}
