#include "play_state.h"

PlayState::PlayState(leng::GameStateManager& stateManager, leng::Window& window) : GameState(stateManager, window) { }

PlayState::~PlayState() { }

void PlayState::init() {
    leng::Shader shader("assets/shaders/pong.vert", "assets/shaders/pong.frag");

    renderer.initVAO(shader);

    camera.init(800, 600);
    camera.setScale(1.0f);
    camera.update();
}

void PlayState::handleEvents(leng::InputManager& inputManager) {
    if(inputManager.isPressed(SDLK_UP))
	player.upHeld = true;
    if(inputManager.isPressed(SDLK_DOWN))
	player.downHeld = true;
    if(inputManager.isReleased(SDLK_UP))
	player.upHeld = false;
    if(inputManager.isReleased(SDLK_DOWN))
	player.downHeld = false;
}

void PlayState::update(float deltaTime) {
    doCollisions();
    camera.update();
    player.update(deltaTime);
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

    renderer.draw(player.sprite);
	
    // Swap buffers
    window.swapWindow();
}

void PlayState::doCollisions() {
}
