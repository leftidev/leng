#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "input_manager.h"
#include "camera_3d.h"
#include "shader.h"
#include "sprite.h"
#include "renderer.h"
#include "player.h"
#include "light.h"
#include "chunk.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float SCREEN_WIDTH = 1024.0f;
float SCREEN_HEIGHT = 768.0f;

// Deltatime
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;  	// Time of last frame

leng::Camera3D camera(glm::vec3(0.0f, 0.0f, -500.0f));

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


void handleEvents(leng::Player& player, leng::InputManager& inputManager) {
    // Camera input
    if(inputManager.isPressed(SDLK_i))
	camera.handleKeyboard(FORWARD, deltaTime);
    if(inputManager.isPressed(SDLK_k))
	camera.handleKeyboard(BACKWARD, deltaTime);
    if(inputManager.isPressed(SDLK_LEFT))
	camera.handleKeyboard(LEFT, deltaTime);
    if(inputManager.isPressed(SDLK_RIGHT))
	camera.handleKeyboard(RIGHT, deltaTime);
    if(inputManager.isPressed(SDLK_UP))
	camera.handleKeyboard(UP, deltaTime);
    if(inputManager.isPressed(SDLK_DOWN))
	camera.handleKeyboard(DOWN, deltaTime);
    
    // Player input
    if(inputManager.isPressed(SDLK_w))
	player.upHeld = true;
    if(inputManager.isPressed(SDLK_s))
	player.downHeld = true;
    if(inputManager.isPressed(SDLK_d))
	player.rightHeld = true;
    if(inputManager.isPressed(SDLK_a))
	player.leftHeld = true;
    
    if(inputManager.isReleased(SDLK_w))
	player.upHeld = false;
    if(inputManager.isReleased(SDLK_s))
	player.downHeld = false;
    if(inputManager.isReleased(SDLK_d))
	player.rightHeld = false;
    if(inputManager.isReleased(SDLK_a))
	player.leftHeld = false;
}

void update(leng::Player& player, float deltaTime) {
    player.update(deltaTime);
}

int main() {
    leng::Window window("OpenGL Tuts", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.setVsync(true);
    //window.enableDepthTest();

    camera.movementSpeed = 0.5f;

    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    //camera.Pitch = -89.0f;
    //camera.Yaw = 90.0f;
    //camera.updateCameraVectors();
    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    //SDL_ShowCursor(SDL_DISABLE);
    const int SIZE = 40;

    std::vector<leng::Sprite> sprites;
    
    for(int x = 0; x < SIZE; x++) {
	for(int y = 0; y < SIZE; y++) {
	    leng::Sprite sprite(x * 64, y * 64, 64, 64, "assets/textures/dungeon_floor.png");
	    sprites.push_back(sprite);
	}
    }
        // Build and compile our shader program
    leng::Shader lightingShader("assets/shaders/lighting.vert", "assets/shaders/lighting.frag");
    leng::Shader lampShader("assets/shaders/lamp.vert", "assets/shaders/lamp.frag");


    
    glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  -5.0f),
	glm::vec3( 2.3f, -3.3f, -8.0f),
	glm::vec3(-4.0f,  2.0f, -1.0f),
	glm::vec3( 0.0f,  0.0f, -1.0f)
};
    
    leng::Renderer renderer;
    renderer.initLightVAO(lightingShader);
    renderer.initLampVAO(lampShader);

    leng::Sprite sprite(0, 0, 64, 64, "assets/textures/dungeon_floor.png");
    

    leng::Player player(64, 64, 64, 64, "assets/textures/soldier.png");

    leng::PointLight pointLight1;
    pointLight1.position = glm::vec3(player.pos.x + 32, player.pos.y + 32, pointLightPositions[0].z);
    pointLight1.ambient = glm::vec3(1.05f, 1.05f, 1.05f);
    pointLight1.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    pointLight1.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight1.constant = 1.0f;
    pointLight1.linear = 0.0005f;
    pointLight1.quadratic = 0.00002f;

    leng::Renderer* renderer2 = new leng::Renderer;
    leng::Chunk* chunk = new leng::Chunk(0);
    chunk->createMesh(renderer2, lightingShader);
    chunk->position = glm::vec3(0, 0, 0);

        GLuint sand_floor = leng::ResourceManager::getTexture("assets/textures/dungeon_floor.png").id;    
	
    leng::InputManager inputManager;

    float xOffset, yOffset;

    //SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    
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
		//xOffset = SCREEN_WIDTH / 2 - event.motion.x;
		//yOffset = SCREEN_HEIGHT / 2 - event.motion.y;
		//camera.handleMouseMovement(xOffset, yOffset);
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
	handleEvents(player, inputManager);
	update(player, deltaTime);
	//SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	camera.Position = glm::vec3(player.pos.x, player.pos.y, camera.Position.z);
	// Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
        // == ==========================
        // Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index 
        // the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
        // by defining light types as classes and set their values in there, or by using a more efficient uniform approach
        // by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
        // == ==========================
	
        // Directional light
	/*
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), 0.0f, 0.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
	*/
	pointLight1.position = glm::vec3(player.pos.x + 32, player.pos.y + 32, pointLightPositions[0].z);
	pointLight1.updateLight1(lightingShader);
	/*        // Point light 1
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), player.pos.x + 32, player.pos.y + 32, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 1.05f, 1.05f, 1.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.014f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.000007f);
	*/
	/*
        // Point light 2
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032);
        // Point light 3
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032);
        // Point light 4
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032);
	
        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 0, 0, -5.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
	*/

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 10000.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(lightingShader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(lightingShader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	for(unsigned int i = 0; i < sprites.size(); i++) {
	    //renderer.draw(sprites[i], lightingShader);
	}
	renderer.draw(sprite, lightingShader);
	renderer.draw(player.sprite, lightingShader);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sand_floor);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	chunk->render(renderer2, lightingShader);
	
	lampShader.use();
	// Create camera transformations
        view = camera.GetViewMatrix();
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 10000.0f);
        // Get the uniform locations
	modelLoc = glGetUniformLocation(lampShader.Program, "model");
	viewLoc  = glGetUniformLocation(lampShader.Program,  "view");
	projLoc  = glGetUniformLocation(lampShader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	// Render lamp
	renderer.drawLamp(pointLightPositions[0], lampShader);


	
	// Swap buffers
	window.swapWindow();
    }
    
    return 0;
}
