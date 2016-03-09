#include "chunk.h"

namespace leng {
    
Chunk::Chunk() {
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

void Chunk::update(float deltaTime) {

}

void Chunk::render(leng::RendererVoxel* renderer, leng::Camera3D& camera) {
    //renderer->draw(blocks, camera);

        //float x = m_position.x;
        //float y = m_position.y;
        //float z = m_position.z;
        //pRenderer->TranslateWorldMatrix(x, y, z);

    renderer->renderMesh(camera, numVertices);
}
    
    void Chunk::createMesh(leng::RendererVoxel* renderer) {
	renderer->createMesh();

	for (int x = 0; x < CHUNK_SIZE; x++) {
	    for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
		    if(blocks[x][y][z].isActive() == false) {
			// Don't create triangle data for inactive blocks
		    	continue;
		    }
		    createCube(renderer, x, y, z);
		}
	    }
	}
	renderer->finishMesh();
	}
    
    void Chunk::createCube(leng::RendererVoxel* renderer, int x, int y, int z) {    
    float width = leng::BLOCK_RENDER_SIZE;
    float height = leng::BLOCK_RENDER_SIZE;
    float length = leng::BLOCK_RENDER_SIZE;

    Vertex2 front_bl(x * width,         y * height,          z * length,  0.0f, 0.0f);
    Vertex2 front_br(x * width + width, y * height,          z * length,  1.0f, 0.0f);
    Vertex2 front_tr(x * width + width, y * height + height, z * length,  1.0f, 1.0f);
    Vertex2 front_tl(x * width,         y * height + height, z * length,  0.0f, 1.0f);

    Vertex2 back_bl(x * width, y * height,  z * length + length,  0.0f, 0.0f);
    Vertex2 back_br(x * width + width, y * height,  z * length + length,  1.0f, 0.0f);
    Vertex2 back_tr(x * width + width,  y * height + height,  z * length + length,  1.0f, 1.0f);
    Vertex2 back_tl(x * width,  y * height + height, z * length + length,  0.0f, 1.0f);

    Vertex2 left_tr(x * width,  y * height + height,  z * length + length,  1.0f, 0.0f);
    Vertex2 left_tl(x * width,  y * height + height, z * length,  1.0f, 1.0f);
    Vertex2 left_bl(x * width, y * height, z * length,  0.0f, 1.0f);
    Vertex2 left_br(x * width, y * height,  z * length + length,  0.0f, 0.0f);

    Vertex2 right_tl(x * width + width,  y * height + height,  z * length + length,  1.0f, 0.0f);
    Vertex2 right_tr(x * width + width,  y * height + height, z * length,  1.0f, 1.0f);
    Vertex2 right_br(x * width + width, y * height, z * length,  0.0f, 1.0f);
    Vertex2 right_bl(x * width + width, y * height,  z * length + length,  0.0f, 0.0f);

    Vertex2 top_tl(x * width,  y * height + height, z * length,  0.0f, 1.0f);
    Vertex2 top_tr(x * width + width,  y * height + height, z * length,  1.0f, 1.0f);
    Vertex2 top_br(x * width + width,  y * height + height,  z * length + length,  1.0f, 0.0f);
    Vertex2 top_bl(x * width,  y * height + height,  z * length + length,  0.0f, 0.0f);

    Vertex2 bottom_bl(x * width, y * height, z * length,  0.0f, 1.0f);
    Vertex2 bottom_br(x * width + width, y * height, z * length,  1.0f, 1.0f);
    Vertex2 bottom_tr(x * width + width, y * height,  z * length + length,  1.0f, 0.0f);
    Vertex2 bottom_tl(x * width, y * height,  z * length + length,  0.0f, 0.0f);
    

    renderer->addVertexToMesh(0, front_bl);
    renderer->addVertexToMesh(0, front_br);
    renderer->addVertexToMesh(0, front_tr);

    renderer->addVertexToMesh(0, front_tr);
    renderer->addVertexToMesh(0, front_tl);
    renderer->addVertexToMesh(0, front_bl);

    renderer->addVertexToMesh(0, back_bl);
    renderer->addVertexToMesh(0, back_br);
    renderer->addVertexToMesh(0, back_tr);

    renderer->addVertexToMesh(0, back_tr);
    renderer->addVertexToMesh(0, back_tl);
    renderer->addVertexToMesh(0, back_bl);

    renderer->addVertexToMesh(0, left_tr);
    renderer->addVertexToMesh(0, left_tl);
    renderer->addVertexToMesh(0, left_bl);

    renderer->addVertexToMesh(0, left_bl);
    renderer->addVertexToMesh(0, left_br);
    renderer->addVertexToMesh(0, left_tr);

    renderer->addVertexToMesh(0, right_tl);
    renderer->addVertexToMesh(0, right_tr);
    renderer->addVertexToMesh(0, right_br);

    renderer->addVertexToMesh(0, right_br);
    renderer->addVertexToMesh(0, right_bl);
    renderer->addVertexToMesh(0, right_tl);

    renderer->addVertexToMesh(0, top_tl);
    renderer->addVertexToMesh(0, top_tr);
    renderer->addVertexToMesh(0, top_br);

    renderer->addVertexToMesh(0, top_br);
    renderer->addVertexToMesh(0, top_bl);
    renderer->addVertexToMesh(0, top_tl);

    renderer->addVertexToMesh(0, bottom_bl);
    renderer->addVertexToMesh(0, bottom_br);
    renderer->addVertexToMesh(0, bottom_tr);

    renderer->addVertexToMesh(0, bottom_tr);
    renderer->addVertexToMesh(0, bottom_tl);
    renderer->addVertexToMesh(0, bottom_bl);

    numVertices += 36;
}
       
} // namespace leng
