#include "GLLightMapCube.h"

float* GLLightMapCube::vertexData = NULL;
unsigned int* GLLightMapCube::indexData = NULL;

GLLightMapCube::GLLightMapCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLObject(translation, rotation, scale)
{
	TextureLoader::setWrap(GL_REPEAT);
	TextureLoader::loadTexture(diffuseTexture, "boxDiffuse.jpg");
	TextureLoader::loadTexture(specularTexture, "boxSpecular.jpg");

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	shader = new Shader("lightMap.vs", "lightMap.fs");

}

void GLLightMapCube::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	GLObject::render(viewMatrix, projMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	shader->setInt("material.texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTexture);
	shader->setInt("material.texture_specular1", 1);

	shader->setFloat("material.shininess", 64.0f);

	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void GLLightMapCube::initVertexData()
{
	vertexData = new float[cubeVertexNum * vertexAttribNum];
	for (int i = 0; i < cubeVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = CUBE_VERTEX_DATA(i, PosX);
		vertexData[i * vertexAttribNum + 1] = CUBE_VERTEX_DATA(i, PosY);
		vertexData[i * vertexAttribNum + 2] = CUBE_VERTEX_DATA(i, PosZ);
		vertexData[i * vertexAttribNum + 3] = CUBE_VERTEX_DATA(i, NormalX);
		vertexData[i * vertexAttribNum + 4] = CUBE_VERTEX_DATA(i, NormalY);
		vertexData[i * vertexAttribNum + 5] = CUBE_VERTEX_DATA(i, NormalZ);
		vertexData[i * vertexAttribNum + 6] = CUBE_VERTEX_DATA(i, TexU);
		vertexData[i * vertexAttribNum + 7] = CUBE_VERTEX_DATA(i, TexV);
	}
	indexData = new unsigned int[cubeIndexNum];
	for (int i = 0; i < cubeIndexNum; ++i) {
		indexData[i] = CUBE_INDEX_DATA(i);
	}
}
