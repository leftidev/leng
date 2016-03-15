#include "play_state.h"

PlayState::PlayState(leng::GameStateManager& stateManager, leng::Window& window, leng::InputManager& inputManager) : GameState(stateManager, window, inputManager) { }

PlayState::~PlayState() { }



void PlayState::init() {
    renderer->initLightVAO(lightingShader);
    renderer->initLampVAO(lampShader);

    camera->init(1024, 768);
    camera->setPosition(glm::vec2(0.0f, 0.0f));
    camera->setScale(0.80f);
    camera->update();
    
    chunk->createMesh(renderer, lightingShader);
    chunk->position = glm::vec3(0, 0, 0);
    
    for(unsigned int i = 0; i < 100; i++) {
	leng::Enemy enemy(500 + (i * 64), 1000, 64, 64, "assets/textures/zombie.png");
	enemies.push_back(enemy);
    }

    // Lights init
    directionalLight->direction = glm::vec3(0.0f, 0.0f, 1.0f);
    directionalLight->ambient = glm::vec3(0.10f, 0.10f, 0.10f);
    directionalLight->diffuse = glm::vec3(0.10f, 0.10f, 0.10f);
    directionalLight->specular = glm::vec3(0.5f, 0.5f, 0.5f);

    pointLight1->position = pointLightPositions[0];
    pointLight1->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    pointLight1->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    pointLight1->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight1->constant = 0.7f;
    pointLight1->linear = 0.0014f;
    pointLight1->quadratic = 0.000007f;

    pointLight2->position = pointLightPositions[1];
    pointLight2->ambient = glm::vec3(0.10f, 0.0f, 0.0f);
    pointLight2->diffuse = glm::vec3(0.8f, 0.0f, 0.0f);
    pointLight2->specular = glm::vec3(1.0f, 0.0f, 0.0f);
    pointLight2->constant = 1.0f;
    pointLight2->linear = 0.0014f;
    pointLight2->quadratic = 0.000007f;

    pointLight3->position = pointLightPositions[2];
    pointLight3->ambient = glm::vec3(0.0f, 0.0f, 0.10f);
    pointLight3->diffuse = glm::vec3(0.0f, 0.0f, 0.8f);
    pointLight3->specular = glm::vec3(0.0f, 0.0f, 1.0f);
    pointLight3->constant = 1.0f;
    pointLight3->linear = 0.007f;
    pointLight3->quadratic = 0.0002f;
    
    pointLight4->position = pointLightPositions[3];
    pointLight4->ambient = glm::vec3(0.0f, 0.10f, 0.0f);
    pointLight4->diffuse = glm::vec3(0.0f, 0.8f, 0.0f);
    pointLight4->specular = glm::vec3(0.0f, 1.0f, 0.0f);
    pointLight4->constant = 1.0f;
    pointLight4->linear = 0.007f;
    pointLight4->quadratic = 0.0002f;

}

void PlayState::handleEvents(leng::InputManager& inputManager, float deltaTime) {
    if(inputManager.isPressed(SDLK_i)) {
	camera->scale += camera->movementSpeed * 0.05f * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager.isPressed(SDLK_k)) {
	camera->scale -= camera->movementSpeed * 0.05f * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager.isPressed(SDLK_LEFT)) {
	//camera->position.x -= camera->movementSpeed * 5 * deltaTime;
        //camera->needsMatrixUpdate = true;
	normalMapping = false;
    }
    if(inputManager.isPressed(SDLK_RIGHT)) {
	//camera->position.x += camera->movementSpeed * 5 * deltaTime;
        //camera->needsMatrixUpdate = true;
	normalMapping = true;
    }
    if(inputManager.isPressed(SDLK_UP)) {
	camera->position.y += camera->movementSpeed * 5 * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager.isPressed(SDLK_DOWN)) {
	camera->position.y -= camera->movementSpeed * 5 * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    
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

void PlayState::update(float deltaTime) {
    doCollisions();
    camera->update();

    if(!freecam) {
	camera->setPosition(glm::vec2(player.pos.x + player.width / 2, player.pos.y + player.height / 2));
    }
	
    player.update(inputManager, camera, deltaTime);
    
    for(unsigned int i = 0; i < enemies.size(); i++) {
	enemies[i].update(player, deltaTime);	
    }
}

void PlayState::draw() {
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

    // Create camera transformations
    glm::mat4 projectionMatrix = camera->getCameraMatrix();
    GLuint cameraLoc = glGetUniformLocation(lightingShader.Program, "transform");
    glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniform1i(glGetUniformLocation(lightingShader.Program, "normalMapping"), normalMapping);

    // Draw tilemap
    chunk->render(renderer, lightingShader);
    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, 0);
    
    // Draw sprites
    renderer->draw(player.sprite, lightingShader);

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

void PlayState::doCollisions() {

}
