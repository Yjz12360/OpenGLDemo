#include "GLSimpleCube.h"

static float cubeVertices[] = {
	// pos              uv
//front
	 -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
	 -0.5f, 0.5f,-0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f,-0.5f, 1.0f, 1.0f,
	  0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
//back
	  0.5f,-0.5f, 0.5f, 0.0f, 0.0f,
	  0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	 -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	 -0.5f,-0.5f, 0.5f, 1.0f, 0.0f,
//left
	 -0.5f,-0.5f, 0.5f, 0.0f, 0.0f,
	 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	 -0.5f, 0.5f,-0.5f, 1.0f, 1.0f,
	 -0.5f,-0.5f,-0.5f, 1.0f, 0.0f,
//right
	  0.5f,-0.5f,-0.5f, 0.0f, 0.0f,
	  0.5f, 0.5f,-0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  0.5f,-0.5f, 0.5f, 1.0f, 0.0f,
//top
	 -0.5f, 0.5f,-0.5f, 0.0f, 0.0f,
	 -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	  0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	  0.5f, 0.5f,-0.5f, 1.0f, 0.0f,
//bottom
	 -0.5f,-0.5f, 0.5f, 0.0f, 0.0f,
	 -0.5f,-0.5f,-0.5f, 0.0f, 1.0f,
	  0.5f,-0.5f,-0.5f, 1.0f, 1.0f,
	  0.5f,-0.5f, 0.5f, 1.0f, 0.0f
};

static unsigned int cubeIndices[] = {
	0,1,2,0,2,3,
	4,5,6,4,6,7,
	8,9,10,8,10,11,
	12,13,14,12,14,15,
	16,17,18,16,18,19,
	20,21,22,20,22,23
};

GLSimpleCube::GLSimpleCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLObject(translation, rotation, scale)
{
	TextureLoader::setWrap(GL_MIRRORED_REPEAT);
	TextureLoader::loadTexture(texture1, "tex3.jpg");
	TextureLoader::setWrap(GL_REPEAT);
	TextureLoader::loadTexture(texture2, "tex2.jpg");

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader = new Shader("simpleCube.vs", "simpleCube.fs");
}

void GLSimpleCube::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	GLObject::render(viewMatrix, projMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	shader->setInt("textureA", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	shader->setInt("textureB", 1);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
