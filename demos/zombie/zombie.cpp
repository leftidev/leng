#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "input_manager.h"
#include "camera_3d.h"
#include "camera_2d.h"
#include "shader.h"
#include "sprite.h"
#include "renderer.h"
#include "player.h"
#include "light.h"
#include "chunk.h"
#include "SpriteBatch.h"
#include "Entity.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/////////////////////////////////////////////
//// TODO
//// -Delete pointers at end of application
//// -Make camera a pointer
/////////////////////////////////////////////
float SCREEN_WIDTH = 1024.0f;
float SCREEN_HEIGHT = 768.0f;

// Deltatime
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;  	// Time of last frame

bool freecam = false;

void handleEvents(leng::Camera2D* camera, leng::Player& player, leng::InputManager* inputManager) {
    if(inputManager->isPressed(SDLK_i)) {
	camera->scale += camera->movementSpeed * 0.05f;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_k)) {
	camera->scale -= camera->movementSpeed * 0.05f;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_LEFT)) {
	camera->position.x -= camera->movementSpeed * 5;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_RIGHT)) {
	camera->position.x += camera->movementSpeed * 5;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_UP)) {
	camera->position.y += camera->movementSpeed * 5;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_DOWN)) {
	camera->position.y -= camera->movementSpeed * 5;
        camera->needsMatrixUpdate = true;	
    }
    
    // Player input
    if(inputManager->isPressed(SDLK_w))
	player.upHeld = true;
    if(inputManager->isPressed(SDLK_s))
	player.downHeld = true;
    if(inputManager->isPressed(SDLK_d))
	player.rightHeld = true;
    if(inputManager->isPressed(SDLK_a))
	player.leftHeld = true;
    
    if(inputManager->isReleased(SDLK_w))
	player.upHeld = false;
    if(inputManager->isReleased(SDLK_s))
	player.downHeld = false;
    if(inputManager->isReleased(SDLK_d))
	player.rightHeld = false;
    if(inputManager->isReleased(SDLK_a))
	player.leftHeld = false;
}

wdvoid update(leng::Player& player, float deltaTime) {
    player.update(deltaTime);
}

int main() {
    leng::Window window("OpenGL Tuts", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.setVsync(true);
    //window.enableDepthTest();
    
    leng::Camera2D* camera = new leng::Camera2D;
    camera->init(800, 600);
    camera->setPosition(glm::vec2(0.0f, 0.0f));
    camera->setScale(0.5f);
    camera->update();

    //SDL_SetWindowFullscreen(window.window, SDL_WINDOW_FULLSCREEN);

    // Hide cursor and trap mouse to window
    //SDL_SetRelativeMouseMode(SDL_TRUE);
    //SDL_ShowCursor(SDL_DISABLE);
    
    // Build and compile our shader program
    leng::Shader lightingShader("assets/shaders/lighting.vert", "assets/shaders/lighting.frag");
    leng::Shader lampShader("assets/shaders/lamp.vert", "assets/shaders/lamp.frag");

    glm::vec3 pointLightPositions[] = {
	glm::vec3( 0.7f,  0.2f,  -5.0f),
	glm::vec3( 2.3f, -3.3f, -50.0f), // red
	glm::vec3(-4.0f,  2.0f, -100.0f), // blue
	glm::vec3( 0.0f,  0.0f, -200.0f) // green
};
    
    leng::Renderer* renderer = new leng::Renderer;
    renderer->initLightVAO(lightingShader);
    renderer->initLampVAO(lampShader);
    
    leng::Chunk* chunk = new leng::Chunk(0);
    chunk->createMesh(renderer, lightingShader);
    chunk->position = glm::vec3(0, 0, 0);
    GLuint dungeon_floor = leng::ResourceManager::getTexture("assets/textures/dungeon_floor.png").id;    
    
    leng::Sprite sprite(0, 0, 64, 64, "assets/textures/dungeon_floor.png");
    

    leng::Player player(64, 64, 64, 64, "assets/textures/soldier.png");

    leng::DirectionalLight* directionalLight = new leng::DirectionalLight;
    directionalLight->direction = glm::vec3(0.0f, 0.0f, 1.0f);
    directionalLight->ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    directionalLight->diffuse = glm::vec3(0.05f, 0.05f, 0.05f);
    directionalLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	
    leng::PointLight* pointLight1 = new leng::PointLight;
    pointLight1->position = glm::vec3(player.pos.x + 32, player.pos.y + 32, pointLightPositions[0].z);
    pointLight1->ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight1->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    pointLight1->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight1->constant = 1.0f;
    pointLight1->linear = 0.0014f;
    pointLight1->quadratic = 0.0007f;

    leng::PointLight* pointLight2 = new leng::PointLight;
    pointLight2->position = glm::vec3(200, 200, pointLightPositions[1].z);
    pointLight2->ambient = glm::vec3(1.0f, 0.0f, 0.0f);
    pointLight2->diffuse = glm::vec3(0.8f, 0.0f, 0.0f);
    pointLight2->specular = glm::vec3(1.0f, 0.0f, 0.0f);
    pointLight2->constant = 0.8f;
    pointLight2->linear = 0.0014f;
    pointLight2->quadratic = 0.0007f;

    leng::PointLight* pointLight3 = new leng::PointLight;
    pointLight3->position = glm::vec3(400, 200, pointLightPositions[2].z);
    pointLight3->ambient = glm::vec3(0.0f, 0.0f, 1.0f);
    pointLight3->diffuse = glm::vec3(0.0f, 0.0f, 0.8f);
    pointLight3->specular = glm::vec3(0.0f, 0.0f, 1.0f);
    pointLight3->constant = 0.3f;
    pointLight3->linear = 0.0014f;
    pointLight3->quadratic = 0.0007f;

    leng::PointLight* pointLight4 = new leng::PointLight;
    pointLight4->position = glm::vec3(200, 400, pointLightPositions[3].z);
    pointLight4->ambient = glm::vec3(0.0f, 1.0f, 0.0f);
    pointLight4->diffuse = glm::vec3(0.0f, 0.8f, 0.0f);
    pointLight4->specular = glm::vec3(0.0f, 1.0f, 0.0f);
    pointLight4->constant = 0.6f;
    pointLight4->linear = 0.0014f;
    pointLight4->quadratic = 0.0007f;

    leng::InputManager* inputManager = new leng::InputManager;

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
		inputManager->setMouseCoords(float(event.motion.x), float(event.motion.y));
		//std::cout << event.motion.x << std::endl;
		break;
	    case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE) { running = false; }
		inputManager->handleKeyboardEvent(event);
		break;
	    case SDL_KEYDOWN:
		inputManager->handleKeyboardEvent(event);
		break;
	    case SDL_MOUSEBUTTONUP:
		inputManager->handleMouseEvent(event);
		break;
	    case SDL_MOUSEBUTTONDOWN:
		inputManager->handleMouseEvent(event);
		break;
	    }
	}
	handleEvents(camera, player, inputManager);
	update(player, deltaTime);
	if(!freecam) {
	    camera->setPosition(glm::vec2(player.pos.x, player.pos.y));
	}
	
	camera->update();
	/*
	if(freecam) {
	    SDL_WarpMouseInWindow(window.window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	} else {
	    camera->Position = glm::vec3(player.pos.x, player.pos.y, camera->Position.z);
	}
	*/  	
	// Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera->position.x, camera->position.y, 700.0f);
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
	// Lights
	directionalLight->update(lightingShader);
	
	//pointLight1.position = glm::vec3(player.pos.x + 32, player.pos.y + 32, pointLightPositions[0].z);
	pointLight1->updateLight1(lightingShader);
	pointLight2->updateLight2(lightingShader);
	pointLight3->updateLight3(lightingShader);
	pointLight4->updateLight4(lightingShader);

	/*	
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
	glm::mat4 projectionMatrix = camera->getCameraMatrix();
	GLuint cameraLoc = glGetUniformLocation(lightingShader.Program, "transform");
	glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, dungeon_floor);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);

	// Draw tilemap
	chunk->render(renderer, lightingShader);
	
	// Draw sprites
	renderer->draw(sprite, lightingShader);
	renderer->draw(player.sprite, lightingShader);

	
	lampShader.use();

	// Create camera transformations
	projectionMatrix = camera->getCameraMatrix();
	cameraLoc = glGetUniformLocation(lightingShader.Program, "transform");
	glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	// Render lamp
	renderer->drawLamp(pointLightPositions[0], lampShader);
	
	// Swap buffers
	window.swapWindow();
    }
    
    return 0;
}
