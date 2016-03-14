#ifndef RENDERER_H
#define RENDERER_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "shader.h"
#include "sprite.h"
#include "vertex.h"

#include <vector>

namespace leng {

struct Mesh {
    std::vector<Vertex2> vertexData;
    GLuint VBO;
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    void initLightVAO(leng::Shader& shader);
    void initLampVAO(leng::Shader& shader);
    void updateVertices(leng::Sprite& sprite);
    void setSpriteAngle(leng::Sprite& sprite, float angle);
    void draw(leng::Sprite& sprite, leng::Shader& shader, float angle = 0.0f);
    void drawLamp(glm::vec3 position, leng::Shader& shader);
    void createMesh();
    void addVertexToMesh(int meshID, Vertex2 vert);
    void finishMesh(int meshID, leng::Shader& shader);
    void renderMesh(int numVertices, leng::Shader& shader, const glm::vec3& position);

private:
    GLuint VBO, lampVBO;
    GLuint lightingVAO;
    GLuint lampVAO;
    GLuint tilesVAO;
    GLuint EBO;
    GLuint indices[6];
    glm::mat4 model;
    GLint modelLoc;

    std::vector<Mesh> meshes;
       	
};

}

#endif // RENDERER_H
