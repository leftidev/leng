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

void Chunk::render(leng::RendererVoxel* renderer, leng::Camera3D& camera) {
    renderer->draw(blocks, camera);
}
    /*
    void Chunk::createMesh(leng::RendererVoxel* renderer) {
	//renderer->createMesh(&m_meshID);

	for (int x = 0; x < CHUNK_SIZE; x++) {
	    for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
		    if(blocks[x][y][z].IsActive() == false) {
			// Don't create triangle data for inactive blocks
			continue;
		    }
		    createCube();
		}
	    }
	}
	//renderer->finishMesh(m_meshID);
    }

void Chunk::createCube() {
    // Front bottom left
    glm::vec3 p1(x-Block::BLOCK_RENDER_SIZE, y-Block::BLOCK_RENDER_SIZE, z+Block::BLOCK_RENDER_SIZE);
    // Front bottom right
    glm::vec3 p2(x+Block::BLOCK_RENDER_SIZE, y-Block::BLOCK_RENDER_SIZE, z+Block::BLOCK_RENDER_SIZE);
    // Front top right
    glm::vec3 p3(x+Block::BLOCK_RENDER_SIZE, y+Block::BLOCK_RENDER_SIZE, z+Block::BLOCK_RENDER_SIZE);
    // Front top left
    glm::vec3 p4(x-Block::BLOCK_RENDER_SIZE, y+Block::BLOCK_RENDER_SIZE, z+Block::BLOCK_RENDER_SIZE);
    // Back bottom right
    glm::vec3 p5(x+Block::BLOCK_RENDER_SIZE, y-Block::BLOCK_RENDER_SIZE, z-Block::BLOCK_RENDER_SIZE);
    // Back bottom left
    glm::vec3 p6(x-Block::BLOCK_RENDER_SIZE, y-Block::BLOCK_RENDER_SIZE, z-Block::BLOCK_RENDER_SIZE);
    // Back top left
    glm::vec3 p7(x-Block::BLOCK_RENDER_SIZE, y+Block::BLOCK_RENDER_SIZE, z-Block::BLOCK_RENDER_SIZE);
    // Back top right
    glm::vec3 p8(x+Block::BLOCK_RENDER_SIZE, y+Block::BLOCK_RENDER_SIZE, z-Block::BLOCK_RENDER_SIZE);

    unsigned int v1; unsigned int v2; unsigned int v3; unsigned int v4; unsigned int v5; unsigned int v6; unsigned int v7; unsigned int v8;

    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;
}
    */
} // namespace leng
