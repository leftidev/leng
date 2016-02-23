#include "camera_2d.h"


namespace leng {

Camera2D::Camera2D() {
}

Camera2D::~Camera2D() {
}

void Camera2D::init(int _screen_width, int _screen_height) {
	screen_width = _screen_width;
	screen_height = _screen_height;
	ortho_matrix = glm::ortho(0.0f, (float)screen_width, 0.0f, (float)screen_height);
}

// Updates the camera matrix if needed
void Camera2D::update() {
    // Only update if our position or scale have changed
    if (needs_matrix_update) {
	// Camera Translation
	glm::vec3 translate(-position.x + screen_width / 2, -position.y + screen_height / 2, 0.0f);
	camera_matrix = glm::translate(ortho_matrix, translate);

	// Camera Scale
	glm::vec3 c_scale(scale, scale, 0.0f);
	camera_matrix = glm::scale(glm::mat4(1.0f), c_scale) * camera_matrix;

	needs_matrix_update = false;
    }
}
    
} // namespace leng
