#include "light.h"

namespace leng {
    
void PointLight::updateLight1(leng::Shader& shader) {
    // Point light 1
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].position"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[0].specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].constant"), constant);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].linear"), linear);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[0].quadratic"), quadratic);
}

void PointLight::updateLight2(leng::Shader& shader) {
    // Point light 1
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].position"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[1].specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].constant"), constant);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].linear"), linear);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[1].quadratic"), quadratic);
}

    void PointLight::updateLight3(leng::Shader& shader) {
    // Point light 1
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[2].position"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[2].ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[2].diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[2].specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[2].constant"), constant);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[2].linear"), linear);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[2].quadratic"), quadratic);
}

    void PointLight::updateLight4(leng::Shader& shader) {
    // Point light 1
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[3].position"), position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[3].ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[3].diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "pointLights[3].specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[3].constant"), constant);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[3].linear"), linear);
    glUniform1f(glGetUniformLocation(shader.Program, "pointLights[3].quadratic"), quadratic);
}

void DirectionalLight::update(leng::Shader& shader) {
    // Directional light
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.direction"), direction.x, direction.y, direction.z);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.specular"), specular.x, specular.y, specular.z);
}
    
} // namespace leng
