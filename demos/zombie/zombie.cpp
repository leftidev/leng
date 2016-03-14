#include <cmath>
#include <string>
#include <iostream>

#include <SOIL/SOIL.h>

#include "window.h"
#include "input_manager.h"
#include "camera_2d.h"
#include "shader.h"
#include "sprite.h"
#include "renderer.h"
#include "player.h"
#include "light.h"
#include "chunk.h"
#include "enemy.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/////////////////////////////////////////////
//// TODO
/////////////////////////////////////////////
float SCREEN_WIDTH = 1024.0f;
float SCREEN_HEIGHT = 768.0f;

// Deltatime
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool freecam = false;
bool normalMapping = true;

void handleEvents(leng::Camera2D* camera, leng::Player& player, leng::InputManager* inputManager, float deltaTime) {
    if(inputManager->isPressed(SDLK_i)) {
	camera->scale += camera->movementSpeed * 0.05f * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_k)) {
	camera->scale -= camera->movementSpeed * 0.05f * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_LEFT)) {
	//camera->position.x -= camera->movementSpeed * 5 * deltaTime;
        //camera->needsMatrixUpdate = true;
	normalMapping = false;
    }
    if(inputManager->isPressed(SDLK_RIGHT)) {
	//camera->position.x += camera->movementSpeed * 5 * deltaTime;
        //camera->needsMatrixUpdate = true;
	normalMapping = true;
    }
    if(inputManager->isPressed(SDLK_UP)) {
	camera->position.y += camera->movementSpeed * 5 * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isPressed(SDLK_DOWN)) {
	camera->position.y -= camera->movementSpeed * 5 * deltaTime;
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

void update(leng::Camera2D* camera, leng::InputManager* inputManager, leng::Player& player, std::vector<leng::Enemy>& enemies, float deltaTime) {
    player.update(inputManager, camera, deltaTime);
    for(unsigned int i = 0; i < enemies.size(); i++) {
	enemies[i].update(player, deltaTime);	
    }

    camera->update();
    
    if(!freecam) {
	camera->setPosition(glm::vec2(player.pos.x + player.width / 2, player.pos.y + player.height / 2));
    }


}

int main() {
    leng::Window window("OpenGL Tuts", SCREEN_WIDTH, SCREEN_HEIGHT);
    window.setVsync(true);
    
    leng::Camera2D* camera = new leng::Camera2D;
    camera->init(1024, 768);
    camera->setPosition(glm::vec2(0.0f, 0.0f));
    camera->setScale(0.80f);
    camera->update();
    
    // Build and compile our shader program
    leng::Shader lightingShader("assets/shaders/lighting.vert", "assets/shaders/lighting.frag");
    leng::Shader lampShader("assets/shaders/lamp.vert", "assets/shaders/lamp.frag");


    
    leng::Renderer* renderer = new leng::Renderer;
    renderer->initLightVAO(lightingShader);
    renderer->initLampVAO(lampShader);
    
    leng::Chunk* chunk = new leng::Chunk(0);
    chunk->createMesh(renderer, lightingShader);
    chunk->position = glm::vec3(0, 0, 0);
    GLuint dungeon_floor = leng::ResourceManager::getTexture("assets/textures/dungeon_floor.png").id;    
    GLuint dungeon_floor_n = leng::ResourceManager::getTexture("assets/textures/dungeon_floor_n.png").id;
    
    leng::Player player(1500, 1500, 64, 64, "assets/textures/soldier.png");
    leng::Enemy enemy(1000, 1000, 64, 64, "assets/textures/zombie.png");

    std::vector<leng::Enemy> enemies;
    for(unsigned int i = 0; i < 100; i++) {
	leng::Enemy enemy(500 + (i * 64), 1000, 64, 64, "assets/textures/zombie.png");
	enemies.push_back(enemy);
    }

    glm::vec3 pointLightPositions[] = {
	glm::vec3(1500, 1500, -5.0f), // white
	glm::vec3(200, 200, -5.0f), // red
	glm::vec3(300, 300, -5.0f), // blue
	glm::vec3(700, 700, -5.0f) // green
    };
	
    leng::DirectionalLight* directionalLight = new leng::DirectionalLight;
    directionalLight->direction = glm::vec3(0.0f, 0.0f, 1.0f);
    directionalLight->ambient = glm::vec3(0.10f, 0.10f, 0.10f);
    directionalLight->diffuse = glm::vec3(0.10f, 0.10f, 0.10f);
    directionalLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);
	
    leng::PointLight* pointLight1 = new leng::PointLight;
    pointLight1->position = pointLightPositions[0];
    pointLight1->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    pointLight1->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    pointLight1->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight1->constant = 0.7f;
    pointLight1->linear = 0.0014f;
    pointLight1->quadratic = 0.000007f;

    leng::PointLight* pointLight2 = new leng::PointLight;
    pointLight2->position = pointLightPositions[1];
    pointLight2->ambient = glm::vec3(0.10f, 0.0f, 0.0f);
    pointLight2->diffuse = glm::vec3(0.8f, 0.0f, 0.0f);
    pointLight2->specular = glm::vec3(1.0f, 0.0f, 0.0f);
    pointLight2->constant = 1.0f;
    pointLight2->linear = 0.0014f;
    pointLight2->quadratic = 0.000007f;

    leng::PointLight* pointLight3 = new leng::PointLight;
    pointLight3->position = pointLightPositions[2];
    pointLight3->ambient = glm::vec3(0.0f, 0.0f, 0.10f);
    pointLight3->diffuse = glm::vec3(0.0f, 0.0f, 0.8f);
    pointLight3->specular = glm::vec3(0.0f, 0.0f, 1.0f);
    pointLight3->constant = 1.0f;
    pointLight3->linear = 0.007f;
    pointLight3->quadratic = 0.0002f;

    leng::PointLight* pointLight4 = new leng::PointLight;
    pointLight4->position = pointLightPositions[3];
    pointLight4->ambient = glm::vec3(0.0f, 0.10f, 0.0f);
    pointLight4->diffuse = glm::vec3(0.0f, 0.8f, 0.0f);
    pointLight4->specular = glm::vec3(0.0f, 1.0f, 0.0f);
    pointLight4->constant = 1.0f;
    pointLight4->linear = 0.007f;
    pointLight4->quadratic = 0.0002f;

    leng::InputManager* inputManager = new leng::InputManager;

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
	handleEvents(camera, player, inputManager, deltaTime);
	update(camera, inputManager, player, enemies, deltaTime);

	// Rendering
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.use();
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera->position.x, camera->position.y, 700.0f);
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
	// Update lights
	//directionalLight->update(lightingShader);
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
	glUniform1i(glGetUniformLocation(lightingShader.Program, "normalMapping"), normalMapping);
	// Bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, dungeon_floor);
	// Bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, dungeon_floor_n);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.normalMap"), 1);

	// Draw tilemap
	chunk->render(renderer, lightingShader);
	
	glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
	// Draw sprites
	renderer->draw(player.sprite, lightingShader);
	renderer->draw(enemy.sprite, lightingShader);

	for(unsigned int i = 0; i < enemies.size(); i++) {
	renderer->draw(enemies[i].sprite, lightingShader);
	}

	lampShader.use();

	// Create camera transformations
	projectionMatrix = camera->getCameraMatrix();
	cameraLoc = glGetUniformLocation(lightingShader.Program, "transform");
	glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	// Render lamp
	/*
	renderer->drawLamp(pointLightPositions[0], lampShader);
	renderer->drawLamp(pointLightPositions[1], lampShader);
	renderer->drawLamp(pointLightPositions[2], lampShader);
	renderer->drawLamp(pointLightPositions[3], lampShader);
	*/
	// Swap buffers
	window.swapWindow();
    }

    delete camera;
    delete renderer;
    delete chunk;
    delete directionalLight;
    delete pointLight1;
    delete pointLight2;
    delete pointLight3;
    delete pointLight4;
    delete inputManager;
    
    return 0;
}
