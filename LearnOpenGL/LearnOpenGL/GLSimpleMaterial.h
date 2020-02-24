#pragma once

#ifndef GL_SIMPLE_MATERIAL_H
#define GL_SIMPLE_MATERIAL_H

#include "GLObject.h"
#include "CubeVertexData.h"

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material() :
		ambient(glm::vec3(1.0f)),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f)),
		shininess(32.0f){};
	Material(glm::vec3 ambient, glm::vec3 diffuse,
		glm::vec3 specular, float shininess) :
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		shininess(shininess) {};
};

class GLSimpleMaterial :public GLObject {
public:
	GLSimpleMaterial(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void setColor(glm::vec3 color);
	void setMaterial(Material material);

	static void initVertexData();
private:
	const static unsigned int vertexNum = cubeVertexNum;
	const static unsigned int vertexAttribNum = 6;
	const static unsigned int vertexDataSize = sizeof(float) * vertexNum * vertexAttribNum;
	const static unsigned int indexNum = cubeIndexNum;
	const static unsigned int indexDataSize = sizeof(unsigned int) * indexNum;

	static float* vertexData;
	static unsigned int* indexData;

	glm::vec3 objectColor;

	Material material;
};

#endif
