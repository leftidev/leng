#include "play_state.h"

PlayState::PlayState(leng::GameStateManager* stateManager, leng::Window* window, leng::InputManager* inputManager) : GameState(stateManager, window, inputManager) { }

PlayState::~PlayState() { }

void PlayState::init() {
    leng::Shader shader("assets/shaders/gizmo.vert", "assets/shaders/gizmo.frag");

    renderer.initVAO(shader);

    camera.init(1680, 1050);
    camera.setPosition(glm::vec2(0.0f, 0.0f));
    camera.setScale(0.5f);
    camera.update();
    
    //ball.vel.x = 0.5f;
    //ball.vel.y = 0.5f;
    //ball.moving = true;    
    //player.sprite.setAngle(150.0f);
    for(unsigned int i = 0; i < 100; i++) {
	leng::Entity* temp = new leng::Entity(i * 52, -1200, 52, 52, "assets/textures/grass_block_52x52.png");
	tiles.push_back(temp);	
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
    if(inputManager->isKeyDown(SDLK_LEFT)) {
	camera.position.x -= camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;
	player.upHeld = true;
    }
    if(inputManager->isKeyDown(SDLK_RIGHT)) {
	camera.position.x += camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;
    }
    if(inputManager->isKeyDown(SDLK_UP)) {
	camera.position.y += camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;	
    }
    if(inputManager->isKeyDown(SDLK_DOWN)) {
	camera.position.y -= camera.movementSpeed * 5 * deltaTime;
        camera.needsMatrixUpdate = true;	
    }
    
    // Player input
    if(inputManager->isKeyDown(SDLK_w))
	player.upHeld = true;
    else
	player.upHeld = false;
    
    if(inputManager->isKeyDown(SDLK_s))
	player.downHeld = true;
    else
	player.downHeld = false;
    
    if(inputManager->isKeyDown(SDLK_d))
	player.rightHeld = true;
    else
	player.rightHeld = false;
    
    if(inputManager->isKeyDown(SDLK_a))
	player.leftHeld = true;
    else
	player.leftHeld = false;

    if(inputManager->isKeyPressed(SDLK_SPACE)) {
	if(player.canDoubleJump) {
	    player.doubleJump();
	}
	if(!player.jumped) {
	    player.jump();	    
	}
    }

}

void PlayState::update(float deltaTime) {
    doCollisions();
    camera.update();
    player.update(tiles, deltaTime);
    enemy.update(ball, deltaTime);
    ball.update();
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

    renderer.draw(midLine);
    renderer.draw(player.sprite);
    renderer.draw(enemy.sprite);
    renderer.draw(ball.sprite);
    for(unsigned int i = 0; i < tiles.size(); i++) {
	renderer.draw(tiles[i]->sprite);
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
