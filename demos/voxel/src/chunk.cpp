#include "chunk.h"

namespace leng {
    
Chunk::Chunk()
{
    // Create the blocks
    blocks = new Block**[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        blocks[i] = new Block*[CHUNK_SIZE];

        for(int j = 0; j < CHUNK_SIZE; j++) {
            blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
}

Chunk::~Chunk()
{
    // Delete the blocks
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            delete [] blocks[i][j];
        }
        delete [] blocks[i];
    }
    delete [] blocks;
}

void Chunk::update(float deltaTime) {

}

void Chunk::render(leng::Renderer3D* renderer, leng::Camera3D& camera) {
    renderer->draw(blocks, camera);
}

} // namespace leng
