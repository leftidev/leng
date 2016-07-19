#include "play_state.h"

PlayState::PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager, int CurrentLevel) : GameState(stateManager, window, inputManager), currentLevel(CurrentLevel) { }

PlayState::~PlayState() { }

void PlayState::init() {
    leng::Shader shader("assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag");

    renderer.initVAO(shader);

    camera.init(1680, 1050);
    camera.setPosition(glm::vec2(0.0f, 0.0f));
    camera.setScale(0.5f);
    camera.update();
        
    initLevel();

    player = new leng::Player(level->startPlayerPos.x, level->startPlayerPos.y, 52, 52, "assets/textures/gizmo_52x52.png");
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

}

void PlayState::update(float deltaTime) {
    doCollisions();
    
    if(!freeCam) {
	camera.setPosition(glm::vec2(player->position.x, player->position.y));	
    }
    
    camera.update();
    player->update(level->blocks, deltaTime);

    // Player touches exit block
    if(player->levelCompleted) {
	currentLevel++;
	stateManager->changeGameState(new PlayState(stateManager, window, inputManager, currentLevel));
    }
    
    // Player dies when going out of level bounds
    if(player->position.y < -400 || player->position.y > level->levelHeight + 400) {
	restartLevel();
    }
    for (unsigned int i = 0; i < level->enemies.size(); i++) {
	level->enemies[i]->update(level->blocks, deltaTime);
    }
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
	stateManager->changeGameState(new PlayState(stateManager, window, inputManager, currentLevel));    
}
