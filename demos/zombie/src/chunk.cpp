#include "chunk.h"

namespace leng {
    
Chunk::Chunk(int MeshID) : meshID(MeshID) {
    numVertices = 0;
    // Create the blocks
    blocks = new Block*[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        blocks[i] = new Block[CHUNK_SIZE];
    }

}

Chunk::~Chunk() {
    // Delete the blocks
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        delete [] blocks[i];
    }
    delete [] blocks;
}

void Chunk::update(float deltaTime) { }

void Chunk::render(leng::Renderer* renderer, leng::Shader& shader) {
    renderer->renderMesh(meshID, numVertices, shader, position);
}
    
void Chunk::createMesh(leng::Renderer* renderer, leng::Shader& voxelShader) {
    renderer->createMesh();
    
    for (int x = 0; x < CHUNK_SIZE; x++) {
	for (int y = 0; y < CHUNK_SIZE; y++) {
	    // Block is active
	    createCube(renderer, x, y);
	}
    }
    renderer->finishMesh(meshID, voxelShader);
}
   
void Chunk::createCube(leng::Renderer* renderer, int x, int y) {    
    float width = leng::BLOCK_RENDER_SIZE;
    float height = leng::BLOCK_RENDER_SIZE;

    Vertex2 front_bl(x * width, y * height, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
    Vertex2 front_br(x * width + width, y * height, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
    Vertex2 front_tr(x * width + width,  y * height + height, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
    Vertex2 front_tl(x * width, y * height + height, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);

    // Triangle 1
    renderer->addVertexToMesh(meshID, front_bl);
    renderer->addVertexToMesh(meshID, front_br);
    renderer->addVertexToMesh(meshID, front_tr);
    // Triangle 2
    renderer->addVertexToMesh(meshID, front_tr);
    renderer->addVertexToMesh(meshID, front_tl);
    renderer->addVertexToMesh(meshID, front_bl);

    numVertices += 6;
}
       
} // namespace leng
