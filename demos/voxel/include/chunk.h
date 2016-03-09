#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "block.h"
#include "renderer_voxel.h"
#include "camera_3d.h"

namespace leng {

static const int CHUNK_SIZE = 16;

class Chunk {
public:
    Chunk();
    ~Chunk();

    void update(float deltaTime);
    void render(leng::RendererVoxel* renderer, leng::Camera3D& camera);
    void createMesh(leng::RendererVoxel* renderer);
    void createCube(leng::RendererVoxel* renderer, int x, int y, int z);

    // The blocks data
    Block*** blocks;
private:

    //leng::Mesh meshID;
    GLuint numVertices;
};

} // namespace leng

#endif // CHUNK_H
