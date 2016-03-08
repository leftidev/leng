#include "renderer_3d.h"

namespace leng {
    
Renderer3D::Renderer3D() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    initVAO();
}

Renderer3D::~Renderer3D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
    
void Renderer3D::initVAO() {
        GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Enable shader attributes
    voxelShader.enableAttribute("position", 3, 5, (GLvoid*)0);
    //shader_program.enable_attribute("color", 3, 8, (GLvoid*)(3 * sizeof(GLfloat)));
    voxelShader.enableAttribute("texCoord", 2, 5, (GLvoid*)(3 * sizeof(GLfloat)));
    
    glBindVertexArray(0);
}

    void Renderer3D::draw(glm::vec3 cubePositions[NUM_BLOCKS][NUM_BLOCKS][NUM_BLOCKS], GLuint textureID, leng::Camera3D& camera) {
	// Rendering
        glClearColor(0.5f, 0.8f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Bind Textures using texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
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
	for(int x = 0; x < NUM_BLOCKS; x++) {
	    for(int y = 0; y < NUM_BLOCKS; y++) {
		for(int z = 0; z < NUM_BLOCKS; z++) {
		    model = glm::mat4();
		    model = glm::translate(model, glm::vec3(x, y, z));
		    //GLfloat angle = 20.0f * x; 
		    //model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
		    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		    glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	    }
	}
	glBindVertexArray(0); 
}
    
} // namespace leng
