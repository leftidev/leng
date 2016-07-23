#include "play_state.h"

PlayState::PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager, int CurrentLevel) : GameState(stateManager, window, inputManager), currentLevel(CurrentLevel) { }

PlayState::~PlayState() {
    delete player;
    delete level;
}

void PlayState::init() {
    leng::Shader shader("assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag");
    
    renderer.initVAO(shader);
    
    camera.init(1680, 1050);
    camera.setPosition(glm::vec2(0.0f, 0.0f));
    camera.setScale(1.0f);
    camera.update();
        
    initLevel();

    player = new leng::Player(level->startPlayerPos.x, level->startPlayerPos.y, 52, 52, "assets/textures/gizmo_52x52.png");

    elapsedTimeTimer.start();
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
    //doCollisions();
    
    if(!freeCam) {
	camera.setPosition(glm::vec2(player->position.x, player->position.y));	
    }
    
    camera.update();
    
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
	stateManager->changeGameState(new PlayState(stateManager, window, inputManager, currentLevel));
    }    
    // Player dies when going out of level bounds
    if(player->position.y < -400 || player->position.y > level->levelHeight + 400) {
	player->deaths++;
	player->restart();
	player->respawn = false;
	restartLevel();
    }
    if(player->respawn) {
	player->respawn = false;
	restartLevel();
    }
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
    /*
    // Update HUD elements
    char buffer[32];
    // Time elapsed
    timeSinceLevelStart = elapsedTimeTimer.getTicks() / 1000.0f;
    snprintf(buffer, 32, "Time: %.2f s.", timeSinceLevelStart);    
    timeText.update(glm::vec2(camera.position.x - timeText.surface->w / 2, camera.position.y + window->height / 2 - timeText.surface->h), buffer);
    // Current level
    snprintf(buffer, 32, "Level %i", currentLevel);    
    levelText.update(glm::vec2(camera.position.x - window->width / 2, camera.position.y + window->height / 2 - levelText.surface->h), buffer);
    // Enemies left
    snprintf(buffer, 32, "Enemies left: %i", (int)level->enemies.size());    
    enemiesText.update(glm::vec2(camera.position.x - window->width / 2, camera.position.y - window->height / 2), buffer);
    // Enemies left
    snprintf(buffer, 32, "Deaths: %i", player->deaths);    
    deathsText.update(glm::vec2(camera.position.x + window->width / 2 - deathsText.surface->w, camera.position.y + window->height / 2 - deathsText.surface->h), buffer);
    */
        // Update HUD elements
    char buffer[32];
    // Time elapsed
    timeSinceLevelStart = elapsedTimeTimer.getTicks() / 1000.0f;
    snprintf(buffer, 32, "Time: %.2f s.", timeSinceLevelStart);    
    timeText.update(glm::vec2(camera.position.x, camera.position.y + window->height / 2), buffer);
    // Current level
    snprintf(buffer, 32, "Level %i", currentLevel);    
    levelText.update(glm::vec2(camera.position.x - window->width / 2, camera.position.y + window->height / 2), buffer);
    // Enemies left
    snprintf(buffer, 32, "Enemies left: %i", (int)level->enemies.size());    
    enemiesText.update(glm::vec2(camera.position.x - window->width / 2, camera.position.y - window->height / 2), buffer);
    // Enemies left
    snprintf(buffer, 32, "Deaths: %i", player->deaths);    
    deathsText.update(glm::vec2(camera.position.x + window->width / 2, camera.position.y + window->height / 2), buffer);
    
}

void PlayState::draw() {
    // Rendering
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader.Program, "my_texture"), 0);
	
    shader.use();

    // Grab the camera matrix
    glm::mat4 projectionMatrix = camera.getCameraMatrix();
    GLuint cameraLoc = shader.getUniformLocation("transform");
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
    
    // Swap buffers
    window->swapWindow();
}

void PlayState::doCollisions() {
    /*
    if(doBoxesIntersect(player.aabb, ball.aabb)) {
	ballHitsPlayer.play();
	ball.vel.x *= -1;
    }
    if(doBoxesIntersect(enemy.aabb, ball.aabb)) {
	ballHitsEnemy.play();
	ball.vel.x *= -1;
    }
    // Ball hits goal
    if(ball.pos.x < -SCREEN_WIDTH / 2 || ball.pos.x > SCREEN_WIDTH / 2 - 24) {
	scoringPoint.play();
	ball.pos.x = 0;
	ball.pos.y = 0;
    }
    // Ball hits top or bot border
    if(ball.pos.y < -SCREEN_HEIGHT / 2 || ball.pos.y > SCREEN_HEIGHT / 2 - 24) {
	ball.vel.y *= -1;
    }
    */
}

void PlayState::restartLevel() {
    //stateManager->changeGameState(new PlayState(stateManager, window, inputManager, currentLevel));
    level = nullptr;
    initLevel();
    
    elapsedTimeTimer.stop();
    elapsedTimeTimer.start();
}

void PlayState::TTF() {
    // Initialize TTF
    if(TTF_Init() == -1) {
	printf("TTF_Init error: %s\n", TTF_GetError());
    }
    // load font.ttf at size 16 into font
    TTF_Font *font;
    font = TTF_OpenFont("assets/fonts/centurygothic.ttf", 16);
    if(!font) {
	printf("TTF_OpenFont error: %s\n", TTF_GetError());
	// handle error
    }
    // Render some UTF8 text in blended black to a new surface
    // then blit to the upper left of the screen
    // then free the text surface
    //SDL_Surface *screen;
    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, "Hello World!", color);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    
    SDL_FreeSurface(surface);
 
    // free the font
    TTF_CloseFont(font);
    font = NULL;
    
    // Quit TTF
    TTF_Quit();
}
