#pragma once

#ifndef GL_SIMPLE_MATERIAL_H
#define GL_SIMPLE_MATERIAL_H

#include "GLObject.h"
#include "CubeVertexData.h"
#include "Material.h"


class GLSimpleMaterial :public GLObject {
public:
	GLSimpleMaterial(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);

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

	Material material;
};

#endif
