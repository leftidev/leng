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
    
} // namespace leng
