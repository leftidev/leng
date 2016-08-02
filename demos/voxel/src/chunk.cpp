#include "chunk.h"

namespace leng {
    
Chunk::Chunk(int MeshID) : meshID(MeshID) {
    numVertices = 0;
    // Create the blocks
    blocks = new Block**[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        blocks[i] = new Block*[CHUNK_SIZE];

        for(int j = 0; j < CHUNK_SIZE; j++) {
            blocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
}

Chunk::~Chunk() {
    // Delete the blocks
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            delete [] blocks[i][j];
        }
        delete [] blocks[i];
    }
    delete [] blocks;
}

void Chunk::update(float deltaTime) { }

    void Chunk::render(leng::RendererVoxel* renderer, leng::Shader& shader) {
    //float x = m_position.x;
    //float y = m_position.y;
    //float z = m_position.z;
    //pRenderer->TranslateWorldMatrix(x, y, z);

	renderer->renderMesh(numVertices, shader, position);
}
    
void Chunk::createMesh(leng::RendererVoxel* renderer, leng::Shader& voxelShader) {
    renderer->createMesh();

    bool lDefault = true;
    
    for (int x = 0; x < CHUNK_SIZE; x++) {
	for (int y = 0; y < CHUNK_SIZE; y++) {
	    for (int z = 0; z < CHUNK_SIZE; z++) {
		if(blocks[x][y][z].isActive() == false) {
		    // Don't create triangle data for inactive blocks
		    continue;
		}
		// Block is active
		createCube(renderer, x, y, z);
	    }
	}
    }
    renderer->finishMesh(meshID, voxelShader);
}
    
void Chunk::createCube(leng::RendererVoxel* renderer, int x, int y, int z) {    
    float width = leng::BLOCK_RENDER_SIZE;
    float height = leng::BLOCK_RENDER_SIZE;
    float length = leng::BLOCK_RENDER_SIZE;

    Vertex2 front_bl(x * width,         y * height,          z * length, 0.0f, 0.0f);
    Vertex2 front_br(x * width + width, y * height,          z * length, 1.0f, 0.0f);
    Vertex2 front_tr(x * width + width, y * height + height, z * length, 1.0f, 1.0f);
    Vertex2 front_tl(x * width,         y * height + height, z * length, 0.0f, 1.0f);

    Vertex2 back_bl(x * width,         y * height,          z * length + length, 0.0f, 0.0f);
    Vertex2 back_br(x * width + width, y * height,          z * length + length, 1.0f, 0.0f);
    Vertex2 back_tr(x * width + width, y * height + height, z * length + length, 1.0f, 1.0f);
    Vertex2 back_tl(x * width,         y * height + height, z * length + length, 0.0f, 1.0f);

    Vertex2 left_tr(x * width, y * height + height, z * length + length, 1.0f, 0.0f);
    Vertex2 left_tl(x * width, y * height + height, z * length,          1.0f, 1.0f);
    Vertex2 left_bl(x * width, y * height,          z * length,          0.0f, 1.0f);
    Vertex2 left_br(x * width, y * height,          z * length + length, 0.0f, 0.0f);

    Vertex2 right_tl(x * width + width, y * height + height, z * length + length, 1.0f, 0.0f);
    Vertex2 right_tr(x * width + width, y * height + height, z * length,          1.0f, 1.0f);
    Vertex2 right_br(x * width + width, y * height,          z * length,          0.0f, 1.0f);
    Vertex2 right_bl(x * width + width, y * height,          z * length + length, 0.0f, 0.0f);

    Vertex2 top_tl(x * width,         y * height + height, z * length,          0.0f, 1.0f);
    Vertex2 top_tr(x * width + width, y * height + height, z * length,          1.0f, 1.0f);
    Vertex2 top_br(x * width + width, y * height + height, z * length + length, 1.0f, 0.0f);
    Vertex2 top_bl(x * width,         y * height + height, z * length + length, 0.0f, 0.0f);

    Vertex2 bottom_bl(x * width,         y * height, z * length,          0.0f, 1.0f);
    Vertex2 bottom_br(x * width + width, y * height, z * length,          1.0f, 1.0f);
    Vertex2 bottom_tr(x * width + width, y * height, z * length + length, 1.0f, 0.0f);
    Vertex2 bottom_tl(x * width,         y * height, z * length + length, 0.0f, 0.0f);
    // Triangle 1
    renderer->addVertexToMesh(meshID, front_bl);
    renderer->addVertexToMesh(meshID, front_br);
    renderer->addVertexToMesh(meshID, front_tr);
    // Triangle 2
    renderer->addVertexToMesh(meshID, front_tr);
    renderer->addVertexToMesh(meshID, front_tl);
    renderer->addVertexToMesh(meshID, front_bl);
    // Triangle 1
    renderer->addVertexToMesh(meshID, back_bl);
    renderer->addVertexToMesh(meshID, back_br);
    renderer->addVertexToMesh(meshID, back_tr);
    // Triangle 2
    renderer->addVertexToMesh(meshID, back_tr);
    renderer->addVertexToMesh(meshID, back_tl);
    renderer->addVertexToMesh(meshID, back_bl);
    // Triangle 1
    renderer->addVertexToMesh(meshID, left_tr);
    renderer->addVertexToMesh(meshID, left_tl);
    renderer->addVertexToMesh(meshID, left_bl);
    // Triangle 2
    renderer->addVertexToMesh(meshID, left_bl);
    renderer->addVertexToMesh(meshID, left_br);
    renderer->addVertexToMesh(meshID, left_tr);
    // Triangle 1
    renderer->addVertexToMesh(meshID, right_tl);
    renderer->addVertexToMesh(meshID, right_tr);
    renderer->addVertexToMesh(meshID, right_br);
    // Triangle 2
    renderer->addVertexToMesh(meshID, right_br);
    renderer->addVertexToMesh(meshID, right_bl);
    renderer->addVertexToMesh(meshID, right_tl);
    // Triangle 1 
    renderer->addVertexToMesh(meshID, top_tl);
    renderer->addVertexToMesh(meshID, top_tr);
    renderer->addVertexToMesh(meshID, top_br);
    // Triangle 2
    renderer->addVertexToMesh(meshID, top_br);
    renderer->addVertexToMesh(meshID, top_bl);
    renderer->addVertexToMesh(meshID, top_tl);
    // Triangle 1
    renderer->addVertexToMesh(meshID, bottom_bl);
    renderer->addVertexToMesh(meshID, bottom_br);
    renderer->addVertexToMesh(meshID, bottom_tr);
    // Triangle 2
    renderer->addVertexToMesh(meshID, bottom_tr);
    renderer->addVertexToMesh(meshID, bottom_tl);
    renderer->addVertexToMesh(meshID, bottom_bl);

    numVertices += 36;
}
       
} // namespace leng
