#include "renderer_3d.h"
#include "chunk.h"
#include <vector>

namespace leng {
    
RendererVoxel::RendererVoxel() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    initVAO();
}

RendererVoxel::~RendererVoxel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
    
void RendererVoxel::initVAO() {
    /*
      std::vector<GLfloat> vertexPositions;
      // Populate vector with vertex positions.
      GLuint bufId = 0;
      glGenBuffers(1, &bufId);
      glBindBuffer(GL_ARRAY_BUFFER, bufId);
      glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat),
      &vertexPositions[0], GL_STATIC_DRAW);
    */
    
    float width = 1.0f * leng::BLOCK_RENDER_SIZE / 2;
    float height = 1.0f * leng::BLOCK_RENDER_SIZE / 2;
    float length = 1.0f * leng::BLOCK_RENDER_SIZE / 2;

    std::vector<Vertex2> vertexPositions2;
    // Triangle 1
    Vertex2 front_bl(-width, -height,  length,  0.0f, 0.0f);
    Vertex2 front_br(width, -height,  length,  1.0f, 0.0f);
    Vertex2 front_tr(width,  height,  length,  1.0f, 1.0f);

    // Triangle 2
    Vertex2 front_tr2(width,  height,  length,  1.0f, 1.0f);
    Vertex2 front_tl(-width,  height,  length,  0.0f, 1.0f);
    Vertex2 front_bl2(-width, -height,  length,  0.0f, 0.0f);
    
    // Triangle 1
    Vertex2 back_bl(-width, -height, -length,  0.0f, 0.0f);
    Vertex2 back_br(width, -height, -length,  1.0f, 0.0f);
    Vertex2 back_tr(width,  height, -length,  1.0f, 1.0f);
    // Triangle 2
    Vertex2 back_tr2(width,  height, -length,  1.0f, 1.0f);
    Vertex2 back_tl(-width,  height, -length,  0.0f, 1.0f);
    Vertex2 back_bl2(-width, -height, -length,  0.0f, 0.0f);

    // Triangle 1
    Vertex2 left_tr(-width,  height,  length,  1.0f, 0.0f);
    Vertex2 left_tl(-width,  height, -length,  1.0f, 1.0f);
    Vertex2 left_bl(-width, -height, -length,  0.0f, 1.0f);
    // Triangle 2
    Vertex2 left_bl2(-width, -height, -length,  0.0f, 1.0f);
    Vertex2 left_br(-width, -height,  length,  0.0f, 0.0f);
    Vertex2 left_tr2(-width,  height,  length,  1.0f, 0.0f);

    // Triangle 1
    Vertex2 right_tr( width,  height,  length,  1.0f, 0.0f);
    Vertex2 right_tl(width,  height, -length,  1.0f, 1.0f);
    Vertex2 right_br(width, -height, -length,  0.0f, 1.0f);
    // Triangle 2
    Vertex2 right_br2(width, -height, -length,  0.0f, 1.0f);
    Vertex2 right_bl(width, -height,  length,  0.0f, 0.0f);
    Vertex2 right_tl2(width,  height,  length,  1.0f, 0.0f);

    // Triangle 1
    Vertex2 top_tl(-width,  height, -length,  0.0f, 1.0f);
    Vertex2 top_tr(width,  height, -length,  1.0f, 1.0f);
    Vertex2 top_br(width,  height,  length,  1.0f, 0.0f);
    // Triangle 2
    Vertex2 top_br2(width,  height,  length,  1.0f, 0.0f);
    Vertex2 top_bl(-width,  height,  length,  0.0f, 0.0f);
    Vertex2 top_tl2(-width,  height, -length,  0.0f, 1.0f);

    // Triangle 1
    Vertex2 bottom_bl(-width, -height, -length,  0.0f, 1.0f);
    Vertex2 bottom_br(width, -height, -length,  1.0f, 1.0f);
    Vertex2 bottom_tr(width, -height,  length,  1.0f, 0.0f);
    // Triangle 2
    Vertex2 bottom_tr2(width, -height,  length,  1.0f, 0.0f);
    Vertex2 bottom_tl(-width, -height,  length,  0.0f, 0.0f);
    Vertex2 bottom_bl2(-width, -height, -length,  0.0f, 1.0f);
    
    // This will store all the vertices that we need to upload
    std::vector<GLfloat> vertexPositions {
	 // Front
	-width, -height,  length,  0.0f, 0.0f, // Bottom-left
	 width, -height,  length,  1.0f, 0.0f, // Bottom-right
	 width,  height,  length,  1.0f, 1.0f, // Top-right
	
	 width,  height,  length,  1.0f, 1.0f, // Top-right
	-width,  height,  length,  0.0f, 1.0f, // Top-left
	-width, -height,  length,  0.0f, 0.0f, // Bottom-left
	// Back
	-width, -height, -length,  0.0f, 0.0f, // Bottom-left
	 width, -height, -length,  1.0f, 0.0f, // Bottom-right
	 width,  height, -length,  1.0f, 1.0f, // Top-right
	
	 width,  height, -length,  1.0f, 1.0f, // Top-right
        -width,  height, -length,  0.0f, 1.0f, // Top-left
        -width, -height, -length,  0.0f, 0.0f, // Bottom-left
	 // Left
        -width,  height,  length,  1.0f, 0.0f, // Top-right
        -width,  height, -length,  1.0f, 1.0f, // Top-left
        -width, -height, -length,  0.0f, 1.0f, // Bottom-left
	
        -width, -height, -length,  0.0f, 1.0f, // Bottom-left
        -width, -height,  length,  0.0f, 0.0f, // Bottom-right
        -width,  height,  length,  1.0f, 0.0f, // Top-right
	 // Right
	 width,  height,  length,  1.0f, 0.0f, // Top-right
	 width,  height, -length,  1.0f, 1.0f, // Top-left
	 width, -height, -length,  0.0f, 1.0f, // Bottom-right
	
	 width, -height, -length,  0.0f, 1.0f, // Bottom-right
	 width, -height,  length,  0.0f, 0.0f, // Bottom-left
	 width,  height,  length,  1.0f, 0.0f, // Top-left
	// Top
        -width,  height, -length,  0.0f, 1.0f, // Top-left
   	 width,  height, -length,  1.0f, 1.0f, // Top-right
	 width,  height,  length,  1.0f, 0.0f, // Bottom-right
	
	 width,  height,  length,  1.0f, 0.0f, // Bottom-right
        -width,  height,  length,  0.0f, 0.0f, // Bottom-left
        -width,  height, -length,  0.0f, 1.0f, // Top-left
         // Bottom
        -width, -height, -length,  0.0f, 1.0f, // Bottom-left
	 width, -height, -length,  1.0f, 1.0f, // Bottom-right
	 width, -height,  length,  1.0f, 0.0f, // Top-right
	
	 width, -height,  length,  1.0f, 0.0f, // Top-right
        -width, -height,  length,  0.0f, 0.0f, // Top-left
        -width, -height, -length,  0.0f, 1.0f  // Bottom-left
	};

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat), &vertexPositions[0], GL_STATIC_DRAW);
    // Enable shader attributes
    voxelShader.enableAttribute("position", 3, 5, (GLvoid*)0);
    //shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    voxelShader.enableAttribute("texCoord", 2, 5, (GLvoid*)(3 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

    void RendererVoxel::draw(leng::Block*** blocks, leng::Camera3D& camera) {

	glUniform1i(glGetUniformLocation(voxelShader.Program, "ourTexture"), 0);
        // Use cooresponding shader when setting uniforms/drawing objects
	voxelShader.use();

	// Create camera transformations
        view = camera.GetViewMatrix();
	projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
        // Get the uniform locations
        modelLoc = glGetUniformLocation(voxelShader.Program, "model");
        viewLoc  = glGetUniformLocation(voxelShader.Program,  "view");
        projLoc  = glGetUniformLocation(voxelShader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Render blocks
	glBindVertexArray(VAO);
	for(int x = 0; x < leng::CHUNK_SIZE; x++) {
	    for(int y = 0; y < leng::CHUNK_SIZE; y++) {
		for(int z = 0; z < leng::CHUNK_SIZE; z++) {
		    if(blocks[x][y][z].isActive()) {
			model = glm::mat4();
			model = glm::translate(model, glm::vec3(x*leng::BLOCK_RENDER_SIZE, y*leng::BLOCK_RENDER_SIZE, z*leng::BLOCK_RENDER_SIZE));
			//GLfloat angle = 20.0f * x; 
			//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		    } else {
			
		    }
		}
	    }
	}
	glBindVertexArray(0); 
}
    
} // namespace leng


