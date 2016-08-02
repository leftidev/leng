#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "shader.h"
#include <string>

namespace leng {
class PointLight {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;

    void updateLight(leng::Shader& shader, const char* lightNr);
};

class DirectionalLight {
public:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void update(leng::Shader& shader);
};

} // namespace leng

#endif // LIGHT_H
