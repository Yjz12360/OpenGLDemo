#pragma once

#include "GLObject.h"
#include "Rect2DVertexData.h"

class GLPostProcessingRect : public GLObject {
public:
	GLPostProcessingRect(const char* vsPath = NULL, const char* fsPath = NULL);

	void renderPostProcess();

	void setTextureBuffer(unsigned int texture);

	static void initVertexData();
private:
	const static unsigned int vertexNum = rect2DVertexNum;
	const static unsigned int vertexAttribNum = 5;
	const static unsigned int vertexDataSize = sizeof(float) * vertexNum * vertexAttribNum;
	const static unsigned int indexNum = rect2DIndexNum;
	const static unsigned int indexDataSize = sizeof(unsigned int) * indexNum;

	static float* vertexData;
	static unsigned int* indexData;

	GLuint texture;
};