#include "GLSimpleMaterial.h"

float* GLSimpleMaterial::vertexData = NULL;
unsigned int* GLSimpleMaterial::indexData = NULL;

GLSimpleMaterial::GLSimpleMaterial(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLObject(translation, rotation, scale)
{
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader = new Shader("simpleMaterial.vs", "simpleMaterial.fs");

}

void GLSimpleMaterial::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	GLObject::render(viewMatrix, projMatrix);

	shader->setVec3("material.ambient", material.ambient);
	shader->setVec3("material.diffuse", material.diffuse);
	shader->setVec3("material.specular", material.specular);
	shader->setFloat("material.shininess", material.shininess);

	shader->setVec3("objectColor", objectColor.x, objectColor.y, objectColor.z);
	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void GLSimpleMaterial::setColor(glm::vec3 color)
{
	objectColor = color;
}

void GLSimpleMaterial::setMaterial(Material material)
{
	this->material = material;
}

void GLSimpleMaterial::initVertexData()
{
	vertexData = new float[cubeVertexNum * vertexAttribNum];
	for (int i = 0; i < cubeVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = CUBE_VERTEX_DATA(i, PosX);
		vertexData[i * vertexAttribNum + 1] = CUBE_VERTEX_DATA(i, PosY);
		vertexData[i * vertexAttribNum + 2] = CUBE_VERTEX_DATA(i, PosZ);
		vertexData[i * vertexAttribNum + 3] = CUBE_VERTEX_DATA(i, NormalX);
		vertexData[i * vertexAttribNum + 4] = CUBE_VERTEX_DATA(i, NormalY);
		vertexData[i * vertexAttribNum + 5] = CUBE_VERTEX_DATA(i, NormalZ);

	}
	indexData = new unsigned int[cubeIndexNum];
	for (int i = 0; i < cubeIndexNum; ++i) {
		indexData[i] = CUBE_INDEX_DATA(i);
	}
}
