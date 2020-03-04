#pragma once

#include "GLObject.h"
#include "TextureLoader.h"
#include "CubeVertexData.h"

class GLSkyBox :public GLObject {
public:
	GLSkyBox(const char* path);

	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void addTextureToShader(Shader* shader);

	static void initVertexData();

private:
	const static unsigned int vertexNum = cubeVertexNum;
	const static unsigned int vertexAttribNum = 3;
	const static unsigned int vertexDataSize = sizeof(float) * vertexNum * vertexAttribNum;
	const static unsigned int indexNum = cubeIndexNum;
	const static unsigned int indexDataSize = sizeof(unsigned int) * indexNum;

	static float* vertexData;
	static unsigned int* indexData;

	unsigned int cubeTexture;
};