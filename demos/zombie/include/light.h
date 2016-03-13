#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "shader.h"

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

    void updateLight1(leng::Shader& shader);
    void updateLight2(leng::Shader& shader);
    void updateLight3(leng::Shader& shader);
    void updateLight4(leng::Shader& shader);
};

} // namespace leng

#endif // LIGHT_H
