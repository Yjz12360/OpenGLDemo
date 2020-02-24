#include "GLPointLight.h"

float* GLPointLight::vertexData = NULL;
unsigned int* GLPointLight::indexData = NULL;

GLPointLight::GLPointLight(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLLightObject(translation,rotation,scale)
{
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader = new Shader("simpleLight.vs", "simpleLight.fs");

	pointLight = PointLight();
}

void GLPointLight::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	GLLightObject::render(viewMatrix, projMatrix);

	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void GLPointLight::initVertexData()
{
	float vertexScale = 0.1f;
	vertexData = new float[cubeVertexNum * vertexAttribNum];
	for (int i = 0; i < cubeVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = CUBE_VERTEX_DATA(i, PosX) * vertexScale;
		vertexData[i * vertexAttribNum + 1] = CUBE_VERTEX_DATA(i, PosY) * vertexScale;
		vertexData[i * vertexAttribNum + 2] = CUBE_VERTEX_DATA(i, PosZ) * vertexScale;
	}
	indexData = new unsigned int[cubeIndexNum];
	for (int i = 0; i < cubeIndexNum; ++i) {
		indexData[i] = CUBE_INDEX_DATA(i);
	}
}

LightType GLPointLight::getLightType()
{
	return Point;
}

const Light * GLPointLight::getLight()
{
	return &pointLight;
}

glm::vec3 GLPointLight::getAmbient()
{
	return pointLight.ambient;
}

glm::vec3 GLPointLight::getDiffuse()
{
	return pointLight.diffuse;
}

glm::vec3 GLPointLight::getSpecular()
{
	return pointLight.specular;
}

void GLPointLight::setAmbient(glm::vec3 ambient)
{
	pointLight.ambient = ambient;
}

void GLPointLight::setDiffuse(glm::vec3 diffuse)
{
	pointLight.diffuse = diffuse;
}

void GLPointLight::setSpecular(glm::vec3 specular)
{
	pointLight.specular = specular;
}
