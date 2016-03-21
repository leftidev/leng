#include "play_state.h"


PlayState::PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager) : GameState(stateManager, window, inputManager) { }

PlayState::~PlayState() {
    delete camera;
    delete renderer;
    delete chunk;
    delete directionalLight;
    delete pointLight1;
    delete pointLight2;
    delete pointLight3;
    delete pointLight4;

    for(unsigned int i = 0; i < enemies.size(); i++) {
	delete enemies[i];
    }
    for(unsigned int i = 0; i < projectiles.size(); i++) {
	delete projectiles[i];
    }
    delete item;
}

void PlayState::init() {
    renderer->initLightVAO(lightingShader);
    renderer->initLampVAO(lampShader);

    camera->init(1680, 1050);
    camera->setPosition(glm::vec2(0.0f, 0.0f));
    camera->setScale(1.2f);
    camera->update();
    
    chunk->createMesh(renderer, lightingShader);
    chunk->position = glm::vec3(0, 0, 0);

    // Lights init
    directionalLight->direction = glm::vec3(0.0f, 0.0f, 1.0f);
    directionalLight->ambient = glm::vec3(0.50f, 0.50f, 0.50f);
    directionalLight->diffuse = glm::vec3(0.10f, 0.10f, 0.10f);
    directionalLight->specular = glm::vec3(0.0f, 0.0f, 0.0f);
    // Center light
    pointLight1->position = pointLightPositions[0];
    pointLight1->ambient = glm::vec3(0.45f, 0.45f, 0.45f);
    pointLight1->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight1->specular = glm::vec3(0.0f, 0.0f, 0.0f);
    pointLight1->constant = 0.9f;
    pointLight1->linear = 0.004f;
    pointLight1->quadratic = 0.000014f;
    // Item light
    pointLight2->position = pointLightPositions[1];
    pointLight2->ambient = glm::vec3(0.3f, 0.3f, 0.0f);
    pointLight2->diffuse = glm::vec3(1.0f, 0.843f, 0.0f);
    pointLight2->specular = glm::vec3(0.0f, 0.0f, 0.0f);
    pointLight2->constant = 1.0f;
    pointLight2->linear = 0.007f;
    pointLight2->quadratic = 0.0002f;
    // Player light
    pointLight3->position = pointLightPositions[2];
    pointLight3->ambient = glm::vec3(0.3f, 0.3f, 0.3f);
    pointLight3->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    pointLight3->specular = glm::vec3(0.0f, 0.0f, 0.0f);
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

    // Zombie spawn timer
    timer.start();

}

void PlayState::handleEvents(leng::InputManager* inputManager, float deltaTime) {
    if(inputManager->isKeyDown(SDLK_i)) {
	camera->scale += camera->movementSpeed * 0.005f * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_k)) {
	camera->scale -= camera->movementSpeed * 0.005f * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_LEFT)) {
	//camera->position.x -= camera->movementSpeed * 5 * deltaTime;
        //camera->needsMatrixUpdate = true;
	normalMapping = false;
    }
    if(inputManager->isKeyDown(SDLK_RIGHT)) {
	//camera->position.x += camera->movementSpeed * 5 * deltaTime;
        //camera->needsMatrixUpdate = true;
	normalMapping = true;
    }
    if(inputManager->isKeyDown(SDLK_UP)) {
	camera->position.y += camera->movementSpeed * 5 * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_DOWN)) {
	camera->position.y -= camera->movementSpeed * 5 * deltaTime;
        camera->needsMatrixUpdate = true;	
    }
    
    // Player input
    if(inputManager->isKeyDown(SDLK_w)){
	player->upHeld = true;
        std::cout << "pos.x: " << player->position.x << " | pos.y: "<< player->position.y << std::endl;
    }
    else
	player->upHeld = false;
    
    if(inputManager->isKeyDown(SDLK_s))
	player->downHeld = true;
    else
	player->downHeld = false;
    
    if(inputManager->isKeyDown(SDLK_d))
	player->rightHeld = true;
    else
	player->rightHeld = false;
    
    if(inputManager->isKeyDown(SDLK_a))
	player->leftHeld = true;
    else
	player->leftHeld = false;
    
    if (inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
	player->shootProjectile(projectiles);
    }
}

void PlayState::update(float deltaTime) {
    doCollisions();
    camera->update();

    if(!freecam) {
	camera->setPosition(glm::vec2(player->position.x + player->width / 2, player->position.y + player->height / 2));
    }
    pointLight3->position = glm::vec3(player->position.x +  player->width / 2, player->position.y +  player->height / 2, pointLightPositions[2].z);
    player->update(inputManager, camera, deltaTime);
    
    for(unsigned int i = 0; i < enemies.size(); i++) {
	enemies[i]->update(player, deltaTime);	
    }

    pointLight2->position = glm::vec3(item->position.x + item->width / 2, item->position.y + item->height / 2, pointLightPositions[3].z);
    
    if(item->render) {
	item->update(deltaTime);
    }

    for(unsigned int i = 0; i < projectiles.size(); i++) {
	projectiles[i]->update(deltaTime);	
    }    

    // Zombie spawner
    if(timer.getTicks() > 2500) {
	timer.stop();
	timer.start();
	
	// initialize random seed
	srand(time(NULL));
	// generate a number between 1 and 4
	spawnPosition = rand() % 4 + 1;
    
	std::cout << spawnPosition << std::endl;
		
	if(spawnPosition == 1) {
	    spawnPositionX = 750;
	    spawnPositionY = rand() % 1400 + 800;
	    
	    leng::Enemy* enemy = new leng::Enemy(spawnPositionX, spawnPositionY, 64, 64, "assets/textures/zombie.png", glm::fvec2(0.15f, 0.15f));
	    enemies.push_back(enemy);
	} else if(spawnPosition == 2) {
	    spawnPositionX = rand() % 1700 + 750;
	    spawnPositionY = 800;
	    
	    leng::Enemy* enemy = new leng::Enemy(spawnPositionX, spawnPositionY, 64, 64, "assets/textures/zombie.png", glm::fvec2(0.15f, 0.15f));
	    enemies.push_back(enemy);
	} else if(spawnPosition == 3) {
	    spawnPositionX = 2450;
	    spawnPositionY = rand() % 1450 + 750;
	    
	    leng::Enemy* enemy = new leng::Enemy(spawnPositionX, spawnPositionY, 64, 64, "assets/textures/zombie.png", glm::fvec2(0.15f, 0.15f));
	    enemies.push_back(enemy);
	} else if(spawnPosition == 4) {
	    spawnPositionX = rand() % 1700 + 750;
	    spawnPositionY = 2200;
	    
	    leng::Enemy* enemy = new leng::Enemy(spawnPositionX, spawnPositionY, 64, 64, "assets/textures/zombie.png", glm::fvec2(0.15f, 0.15f));
	    enemies.push_back(enemy);
	}
    }
    //std::cout << timer.getTicks() << std::endl;  
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
    pointLight1->updateLight(lightingShader, "0");
    pointLight2->updateLight(lightingShader, "1");
    //pointLight3->updateLight(lightingShader, "2");
    //pointLight4->updateLight4(lightingShader);

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
    renderer->draw(player->sprite, lightingShader);
    for(unsigned int i = 0; i < projectiles.size(); i++) {
	renderer->draw(projectiles[i]->sprite, lightingShader);
    }
    for(unsigned int i = 0; i < enemies.size(); i++) {
	renderer->draw(enemies[i]->sprite, lightingShader);
    }
    if(item->render) {
	renderer->draw(item->sprite, lightingShader);	
    }

    lampShader.use();

    // Create camera transformations
    projectionMatrix = camera->getCameraMatrix();
    cameraLoc = glGetUniformLocation(lightingShader.Program, "transform");
    glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
    // Render lamp
    /*
      renderer->drawLamp(pointLight1->position, lampShader);
      renderer->drawLamp(pointLight2->position, lampShader);
      renderer->drawLamp(pointLight3->position, lampShader);
    */      
    //renderer->drawLamp(pointLightPositions[3], lampShader);
    
    // Swap buffers
    window->swapWindow();
}

void PlayState::doCollisions() {
    // Update Zombie collisions
    for (unsigned int i = 0; i < enemies.size(); i++) {
	// Collide with other zombies
	for (unsigned int j = i + 1; j < enemies.size(); j++) {
	    collideWithCircle(enemies[i], enemies[j]);
	}
	// Collide with player
	if (collideWithCircle(enemies[i], player)) {
	    // std::cout << "Enemy hits player!" << std::endl;
	    player->health -= 1;
	    std::cout << player->health << std::endl;
	    
	}
	for(unsigned int j = 0; j < projectiles.size(); j++) {
	    if(doCirclesIntersect(enemies[i], projectiles[j])) {
		enemies.erase(enemies.begin() + i);
		projectiles.erase(projectiles.begin() + j);
	    }
	}
	
    }
    // Collide player with item
    if (doCirclesIntersect(item, player)) {
	player->pickupItem(item);
	item->render = false;
	item->position = glm::vec2(100000, 100000);
    }
}
