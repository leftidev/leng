#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "block.h"
#include "renderer.h"
#include "camera_3d.h"
#include "shader.h"

namespace leng {

static const int CHUNK_SIZE = 20;

class Chunk {
public:
    Chunk(int MeshID);
    ~Chunk();

    void update(float deltaTime);
    void render(leng::Renderer* renderer, leng::Shader& shader);
    void createMesh(leng::Renderer* renderer, leng::Shader& voxelShader);
    void createCube(leng::Renderer* renderer, int x, int y);

    // The blocks data
    Block** blocks;
    glm::vec3 position;
private:
    int meshID;
    GLuint numVertices;

};

} // namespace leng

#endif // CHUNK_H
