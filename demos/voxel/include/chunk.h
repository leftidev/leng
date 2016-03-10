#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "block.h"
#include "renderer_voxel.h"
#include "camera_3d.h"
#include "shader.h"

namespace leng {

static const int CHUNK_SIZE = 16;

class Chunk {
public:
    Chunk(int MeshID);
    ~Chunk();

    void update(float deltaTime);
    void render(leng::RendererVoxel* renderer, leng::Shader& shader);
    void createMesh(leng::RendererVoxel* renderer, leng::Shader& voxelShader);
    void createCube(leng::RendererVoxel* renderer, int x, int y, int z);

    // The blocks data
    Block*** blocks;
    glm::vec3 position;
private:
    int meshID;
    GLuint numVertices;

};

} // namespace leng

#endif // CHUNK_H
