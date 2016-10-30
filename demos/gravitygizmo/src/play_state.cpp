#include "play_state.h"

#include <iostream>

PlayState::PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager, leng::Shader* Shader, int CurrentLevel) : GameState(stateManager, window, inputManager), shader(Shader), currentLevel(CurrentLevel) {
    
    renderer.initVAO();
    
    camera.init(1680, 1050);
    //camera.setPosition(glm::vec2(0.0f, 0.0f));
    camera.setScale(1.0f);
    camera.update();
        
    initLevel();

    player = new leng::Player(level->startPlayerPos.x, level->startPlayerPos.y, 52, 52, "assets/textures/gizmo_52x52.png");

    elapsedTimeTimer.start();
}

PlayState::~PlayState() {
    delete player;
    delete level;
}

void PlayState::initLevel() {
    // Initialize level 1
    if (currentLevel == 1) {
	level = new leng::Level("assets/levels/level01.txt");
    } else if (currentLevel == 2) {
	level = new leng::Level("assets/levels/level02.txt");
    } else if (currentLevel == 3) {
	level = new leng::Level("assets/levels/level03.txt");
    } else if (currentLevel == 4) {
	level = new leng::Level("assets/levels/level04.txt");
    } else if (currentLevel == 5) {
	level = new leng::Level("assets/levels/level05.txt");
    } else if (currentLevel == 6) {
	level = new leng::Level("assets/levels/level06.txt");
    } else if (currentLevel == 7) {
	level = new leng::Level("assets/levels/level07.txt");
    } else if (currentLevel == 8) {
	level = new leng::Level("assets/levels/level08.txt");
    } else if (currentLevel == 9) {
	level = new leng::Level("assets/levels/level09.txt");
    } else if (currentLevel == 10) {
	level = new leng::Level("assets/levels/level10.txt");
    } else if (currentLevel == 11) {
	level = new leng::Level("assets/levels/level11.txt");
    } else if (currentLevel == 12) {
	level = new leng::Level("assets/levels/level12.txt");
    } else if (currentLevel == 13) {
	level = new leng::Level("assets/levels/level13.txt");
    } else if (currentLevel == 14) {
	level = new leng::Level("assets/levels/level14.txt");
    } else if (currentLevel == 15) {
	level = new leng::Level("assets/levels/level15.txt");
    }
}

void PlayState::handleEvents(leng::InputManager* inputManager, float deltaTime) {
    if(inputManager->isKeyDown(SDLK_i)) {
	camera.scale += camera.movementSpeed * 0.005f * deltaTime;
        camera.needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_k)) {
	camera.scale -= camera.movementSpeed * 0.005f * deltaTime;
        camera.needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_a)) {
	camera.position.x -= camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;
    }
    if(inputManager->isKeyDown(SDLK_d)) {
	camera.position.x += camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;
    }
    if(inputManager->isKeyDown(SDLK_w)) {
	camera.position.y += camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_s)) {
	camera.position.y -= camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_f)) {
	if(freeCam) {
	    freeCam = false;
	} else {
	    freeCam = true;
	}
    }    
    // Player input
    if(inputManager->isKeyDown(SDLK_UP))
	player->gravityBendInvert();
    
    if(inputManager->isKeyDown(SDLK_DOWN))
	player->gravityBend();
	
    if(inputManager->isKeyDown(SDLK_RIGHT))
	player->rightHeld = true;
    else
	player->rightHeld = false;
    
    if(inputManager->isKeyDown(SDLK_LEFT))
	player->leftHeld = true;
    else
	player->leftHeld = false;

    if(inputManager->isKeyPressed(SDLK_SPACE)) {
	if(player->canDoubleJump) {
	    player->doubleJump();
	}
	if(!player->jumped) {
	    player->jump();	    
	}
    }
    if(inputManager->isKeyPressed(SDLK_LCTRL)) {
	player->shootBubble();
    }

}

void PlayState::update(float deltaTime) {
    
    if(!freeCam) {
	camera.setPosition(glm::vec2(player->position.x, player->position.y));	
    }
    
    camera.update();
        
    for (unsigned int i = 0; i < level->enemies.size(); i++) {
	level->enemies[i]->update(level->blocks, deltaTime);
	
	if(level->enemies[i]->destroyed) {
	    level->enemies.erase(level->enemies.begin() + i);
	}
    }
    if (level->enemies.empty()) {
	for (unsigned int i = 0; i < level->blocks.size(); i++) {
	    if (level->blocks[i]->type == leng::BlockType::DISAPPEARING) {
		level->blocks.erase(level->blocks.begin() + i);
	    }
	}
    }
    
    // Update HUD elements
    char buffer[32];
    // Time elapsed
    timeSinceLevelStart = elapsedTimeTimer.getTicks() / 1000.0f;
    snprintf(buffer, 32, "Time: %.2f s.", timeSinceLevelStart);    
    timeText.update(glm::vec2(camera.position.x - timeText.sizeSurface->w / 2, camera.position.y + window->height / 2 - timeText.sizeSurface->h), buffer);
    // Current level
    snprintf(buffer, 32, "Level %i", currentLevel);    
    levelText.update(glm::vec2(camera.position.x - window->width / 2, camera.position.y + window->height / 2 - levelText.sizeSurface->h), buffer);
    // Enemies left
    snprintf(buffer, 32, "Enemies left: %i", (int)level->enemies.size());    
    enemiesText.update(glm::vec2(camera.position.x - window->width / 2, camera.position.y - window->height / 2), buffer);
    // Deaths
    snprintf(buffer, 32, "Deaths: %i", player->deaths);    
    deathsText.update(glm::vec2(camera.position.x + window->width / 2 - deathsText.sizeSurface->w, camera.position.y + window->height / 2 - deathsText.sizeSurface->h), buffer);

    player->update(level->blocks, level->enemies, deltaTime);
    
    if(player->bubble) {
	player->bubble->update(level->blocks, level->enemies, deltaTime);
	if(player->bubble->position.x < player->bubble->startPosition.x - player->bubble->PROJECTILE_REACH || player->bubble->position.x > player->bubble->startPosition.x + player->bubble->PROJECTILE_REACH) {
	    player->bubble->destroyed = true;
	}
	if(player->bubble->destroyed) {
	    player->bubble = nullptr;
	}
    }
    // Player touches exit block
    if(player->levelCompleted) {
	currentLevel++;
	stateManager->changeGameState(new PlayState(stateManager, window, inputManager, shader, currentLevel));
    }    
    // Player dies when going out of level bounds
    if(player->position.y < -400 || player->position.y > level->levelHeight + 400) {
	player->deaths++;
	player->restart();

	delete level;
	level = nullptr;
	initLevel();
    
	elapsedTimeTimer.stop();
	elapsedTimeTimer.start();
    }
    if(player->respawn) {
	player->respawn = false;

	delete level;
	level = nullptr;
	initLevel();
    
	elapsedTimeTimer.stop();
	elapsedTimeTimer.start();
    }
}

void PlayState::draw() {
        // Rendering
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader->Program, "my_texture"), 0);
	
    shader->use();

    // Grab the camera matrix
    glm::mat4 projectionMatrix = camera.getCameraMatrix();
    GLuint cameraLoc = shader->getUniformLocation("transform");
    glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    renderer.draw(player->sprite);
    
    // Draw blocks
    for (unsigned int i = 0; i < level->blocks.size(); i++) {
	renderer.draw(level->blocks[i]->sprite);
    }
    // Draw enemies
    for (unsigned int i = 0; i < level->enemies.size(); i++) {
	renderer.draw(level->enemies[i]->sprite);
    }
    if(player->bubble) {
	renderer.draw(player->bubble->sprite);
    }
    
    renderer.drawText(timeText);
    renderer.drawText(levelText);
    renderer.drawText(enemiesText);
    renderer.drawText(deathsText);

    glActiveTexture(0);
    // Swap buffers
    window->swapWindow();
}
