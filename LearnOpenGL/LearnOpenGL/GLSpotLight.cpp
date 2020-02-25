#include "GLSpotLight.h"

const glm::vec3 GLSpotLight::defaultDirection = glm::vec3(0.0f, 0.0f, -1.0f);

float* GLSpotLight::vertexData = NULL;
unsigned int* GLSpotLight::indexData = NULL;

GLSpotLight::GLSpotLight(glm::vec3 translation, glm::vec3 direction)
	:GLLightObject(translation, glm::vec3(0.0f), glm::vec3(1.0f))
{
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader = new Shader("simpleLight.vs", "simpleLight.fs");

	light = SpotLight();
	light.direction = direction;
}

void GLSpotLight::start()
{
	//lookAt(light.direction);
}

void GLSpotLight::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	GLLightObject::render(viewMatrix, projMatrix);

	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void GLSpotLight::initVertexData()
{
	float vertexScale = 0.06f;
	vertexData = new float[cubeVertexNum * vertexAttribNum];
	for (int i = 0; i < cubeVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = CUBE_VERTEX_DATA(i, PosX) * vertexScale * 2;
		vertexData[i * vertexAttribNum + 1] = CUBE_VERTEX_DATA(i, PosY) * vertexScale;
		vertexData[i * vertexAttribNum + 2] = CUBE_VERTEX_DATA(i, PosZ) * vertexScale;
	}
	indexData = new unsigned int[cubeIndexNum];
	for (int i = 0; i < cubeIndexNum; ++i) {
		indexData[i] = CUBE_INDEX_DATA(i);
	}
}

LightType GLSpotLight::getLightType()
{
	return Spot;
}

const Light * GLSpotLight::getLight()
{
	return &light;
}

glm::vec3 GLSpotLight::getAmbient()
{
	return light.ambient;
}

glm::vec3 GLSpotLight::getDiffuse()
{
	return light.diffuse;
}

glm::vec3 GLSpotLight::getSpecular()
{
	return light.specular;
}

void GLSpotLight::setAmbient(glm::vec3 ambient)
{
	light.ambient = ambient;
}

void GLSpotLight::setDiffuse(glm::vec3 diffuse)
{
	light.diffuse = diffuse;
}

void GLSpotLight::setSpecular(glm::vec3 specular)
{
	light.specular = specular;
}
