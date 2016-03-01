#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace leng {
// Camera class for 2D games
class Camera2D {
public:
	Camera2D();
	~Camera2D();

	// Sets up the ortographic matrix and screen dimensions
	void init(int _screen_width, int _screen_height);

	// Updates the camera matrix if needed
	void update();

	// Setters
	void set_position(const glm::vec2& new_position) { position = new_position; needs_matrix_update = true; }
	void set_scale(float new_scale) { scale = new_scale; needs_matrix_update = true; }

	// Getters
	glm::vec2 get_position() { return position; }
	float get_scale() { return scale; }
	glm::mat4 get_camera_matrix() { return camera_matrix; }

private:
	int screen_width, screen_height;
	bool needs_matrix_update {true};
	float scale {1.0f};
	glm::vec2 position;
	glm::mat4 camera_matrix;
	glm::mat4 ortho_matrix;
};

} // namespace leng
#endif // CAMERA_2D_H
