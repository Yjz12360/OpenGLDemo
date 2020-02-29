#include "GLAlphaTexture.h"

float* GLAlphaTexture::vertexData = NULL;
unsigned int* GLAlphaTexture::indexData = NULL;

GLAlphaTexture::GLAlphaTexture(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLObject(translation, rotation, scale)
{

	TextureLoader::setWrap(GL_CLAMP_TO_EDGE);
	TextureLoader::loadTexture(texture, "Resource/Texture/grass.png");

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader = new Shader("alphaTexture.vs", "alphaTexture.fs");
}

void GLAlphaTexture::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{

	GLObject::render(viewMatrix, projMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->setInt("texture", 0);

	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
}

void GLAlphaTexture::initVertexData()
{
	vertexData = new float[rect2DVertexNum * vertexAttribNum];
	for (int i = 0; i < rect2DVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = RECT2D_VERTEX_DATA(i, PosX);
		vertexData[i * vertexAttribNum + 1] = RECT2D_VERTEX_DATA(i, PosY);
		vertexData[i * vertexAttribNum + 2] = RECT2D_VERTEX_DATA(i, PosZ);
		vertexData[i * vertexAttribNum + 3] = RECT2D_VERTEX_DATA(i, TexU);
		vertexData[i * vertexAttribNum + 4] = RECT2D_VERTEX_DATA(i, TexV);
	}
	indexData = new unsigned int[rect2DIndexNum];
	for (int i = 0; i < rect2DIndexNum; ++i) {
		indexData[i] = RECT2D_INDEX_DATA(i);
	}
}
