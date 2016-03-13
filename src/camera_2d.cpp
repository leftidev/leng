#include "camera_2d.h"


namespace leng {

Camera2D::Camera2D()  {
}

Camera2D::~Camera2D() {
}

void Camera2D::init(int ScreenWidth, int ScreenHeight) {
	screenWidth = ScreenWidth;
	screenHeight = ScreenHeight;
	orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
	// Invert Y Direction
	screenCoords.y = screenHeight - screenCoords.y;
	// Make it so that 0 is the center
	screenCoords -= glm::vec2(screenWidth / 2, screenHeight / 2);
	// Scale the coordinates
	screenCoords /= scale;
	// Translate with the camera position
	screenCoords += position;

	return screenCoords;
}
    
// Updates the camera matrix if needed
void Camera2D::update() {
    // Only update if our position or scale have changed
    if (needsMatrixUpdate) {
	// Camera Translation
	glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0.0f);
	cameraMatrix = glm::translate(orthoMatrix, translate);

	// Camera Scale
	glm::vec3 Scale(scale, scale, 0.0f);
	cameraMatrix = glm::scale(glm::mat4(1.0f), Scale) * cameraMatrix;

	needsMatrixUpdate = false;
    }
}

    
// Simple AABB test to see if a box is in the camera view
bool Camera2D::isBoxInView(const glm::vec2& Position, const glm::vec2& dimensions) {
    glm::vec2 scaledScreenDimensions = glm::vec2(screenWidth, screenHeight) / (scale);

    // The minimum distance before a collision occurs
    const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
    const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

    // Center position of the parameters
    glm::vec2 centerPos = Position + dimensions / 2.0f;
    // Center position of the camera
    glm::vec2 centerCameraPos = position;
    // Vector from the input to the camera
    glm::vec2 distVec = centerPos - centerCameraPos;

    // Get the depth of the collision
    float xDepth = MIN_DISTANCE_X - abs(distVec.x);
    float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

    // If either the depths are > 0, then we collided
    if (xDepth > 0 && yDepth > 0) {
	// There was a collision
	return true;
    }
    return false;
}
    
} // namespace leng
