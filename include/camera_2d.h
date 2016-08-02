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
    void init(int ScreenWidth, int ScreenHeight);

    // Updates the camera matrix if needed
    void update();
    glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
    bool isBoxInView(const glm::vec2& position, const glm::vec2& dimensions);

    // Setters
    void setPosition(const glm::vec2& newPosition) { position = newPosition; needsMatrixUpdate = true; }
    void setScale(float newScale) { scale = newScale; needsMatrixUpdate = true; }

    // Getters
    glm::vec2 getPosition() { return position; }
    float get_scale() { return scale; }
    glm::mat4 getCameraMatrix() { return cameraMatrix; }

//private:
    int screenWidth, screenHeight;
    bool needsMatrixUpdate {true};
    float scale {1.0f};
    glm::vec2 position;
    glm::mat4 cameraMatrix;
    glm::mat4 orthoMatrix;

    float movementSpeed {0.5f};
};

} // namespace leng

#endif // CAMERA_2D_H
