#include "GLPostProcessingRect.h"

float* GLPostProcessingRect::vertexData = NULL;
unsigned int* GLPostProcessingRect::indexData = NULL;

GLPostProcessingRect::GLPostProcessingRect(const char * vsPath, const char * fsPath)
	:GLObject()
{
	TextureLoader::loadTexture(texture, "untitled.png");

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if (vsPath != NULL && fsPath != NULL)
		setShader(vsPath, fsPath);
}

void GLPostProcessingRect::renderPostProcess()
{
	if (shader == NULL)return;

	//glDisable(GL_CULL_FACE);

	shader->use();
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->setInt("screenTexture", 0);

	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);

	//glEnable(GL_CULL_FACE);
}

void GLPostProcessingRect::setTextureBuffer(unsigned int texture)
{
	this->texture = texture;
}

void GLPostProcessingRect::initVertexData()
{
	vertexData = new float[rect2DVertexNum * vertexAttribNum];
	for (int i = 0; i < rect2DVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = RECT2D_VERTEX_DATA(i, PosX) * 2;
		vertexData[i * vertexAttribNum + 1] = RECT2D_VERTEX_DATA(i, PosY) * 2;
		vertexData[i * vertexAttribNum + 2] = RECT2D_VERTEX_DATA(i, PosZ);
		vertexData[i * vertexAttribNum + 3] = RECT2D_VERTEX_DATA(i, TexU);
		vertexData[i * vertexAttribNum + 4] = RECT2D_VERTEX_DATA(i, TexV);
	}
	indexData = new unsigned int[rect2DIndexNum];
	for (int i = 0; i < rect2DIndexNum; i++) {
		indexData[i] = RECT2D_INDEX_DATA(i);
	}
	/*for (int i = 0; i < rect2DIndexNum; i += 3) {
		indexData[i] = RECT2D_INDEX_DATA(i);
		indexData[i + 1] = RECT2D_INDEX_DATA((i + 2));
		indexData[i + 2] = RECT2D_INDEX_DATA((i + 1));
	}*/
}
