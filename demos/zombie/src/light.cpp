#include "light.h"
#include "stdio.h"
#include "string.h"

namespace leng {

void PointLight::updateLight(leng::Shader& shader, const char* lightNr) {
    const char* one = "pointLights[";
    
    const char* three = "].position";
    char buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    // Point light 1
    glUniform3f(glGetUniformLocation(shader.Program, buf), position.x, position.y, position.z);

    three = "].ambient";
    buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    glUniform3f(glGetUniformLocation(shader.Program, buf), ambient.x, ambient.y, ambient.z);

    three = "].diffuse";
    buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    glUniform3f(glGetUniformLocation(shader.Program, buf), diffuse.x, diffuse.y, diffuse.z);

    three = "].specular";
    buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    glUniform3f(glGetUniformLocation(shader.Program, buf), specular.x, specular.y, specular.z);

    three = "].constant";
    buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    glUniform1f(glGetUniformLocation(shader.Program, buf), constant);

    three = "].linear";
    buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    glUniform1f(glGetUniformLocation(shader.Program, buf), linear);

    three = "].quadratic";
    buf[100];
    strcpy(buf, one);
    strcat(buf, lightNr);
    strcat(buf, three);
    glUniform1f(glGetUniformLocation(shader.Program, buf), quadratic);	
}
    
} // namespace leng
