#ifndef CHUNK_H
#define CHUNK_H

#include "block.h"
#include "renderer_3d.h"
#include "camera_3d.h"

namespace leng {

static const int CHUNK_SIZE = 16;

class Chunk {
public:
    Chunk();
    ~Chunk();

    void update(float deltaTime);
    void render(leng::Renderer3D* renderer, leng::Camera3D& camera);

private:
    // The blocks data
    Block*** blocks;
};

} // namespace leng

#endif // CHUNK_H
