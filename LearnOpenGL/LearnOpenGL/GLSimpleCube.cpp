#include "GLSimpleCube.h"

float* GLSimpleCube::vertexData = NULL;
unsigned int* GLSimpleCube::indexData = NULL;

GLSimpleCube::GLSimpleCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLObject(translation, rotation, scale)
{
	TextureLoader::setWrap(GL_MIRRORED_REPEAT);
	TextureLoader::loadTexture(texture1, "tex3.jpg");
	TextureLoader::setWrap(GL_REPEAT);
	TextureLoader::loadTexture(texture2, "tex2.jpg");

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)(3 * sizeof(float)));
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
	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void GLSimpleCube::initVertexData()
{
	vertexData = new float[cubeVertexNum * vertexAttribNum];
	for (int i = 0; i < cubeVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = CUBE_VERTEX_DATA(i, PosX);
		vertexData[i * vertexAttribNum + 1] = CUBE_VERTEX_DATA(i, PosY);
		vertexData[i * vertexAttribNum + 2] = CUBE_VERTEX_DATA(i, PosZ);
		vertexData[i * vertexAttribNum + 3] = CUBE_VERTEX_DATA(i, TexU);
		vertexData[i * vertexAttribNum + 4] = CUBE_VERTEX_DATA(i, TexV);
	}
	indexData = new unsigned int[cubeIndexNum];
	for (int i = 0; i < cubeIndexNum; ++i) {
		indexData[i] = CUBE_INDEX_DATA(i);
	}
}

