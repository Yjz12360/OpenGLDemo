#include "GLSkyBox.h"

float* GLSkyBox::vertexData = NULL;
unsigned int* GLSkyBox::indexData = NULL;

GLSkyBox::GLSkyBox(const char* path)
	:GLObject()
{
	TextureLoader::setMinFilter(GL_LINEAR);
	TextureLoader::setMaxFilter(GL_LINEAR);
	TextureLoader::setWrap(GL_CLAMP_TO_EDGE);
	//TextureLoader::setWrap(GL_REPEAT);

	TextureLoader::loadCubeTexture(cubeTexture, path);

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttribNum * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader = new Shader("skybox.vs", "skybox.fs");
}

void GLSkyBox::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));
	GLObject::render(viewMatrix, projMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
	shader->setInt("skybox", 0);
	glDrawElements(GL_TRIANGLES, indexNum, GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}

void GLSkyBox::addTextureToShader(Shader * shader)
{
	if (shader == NULL) return;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
	shader->setInt("skybox", 0);
}

void GLSkyBox::initVertexData()
{
	vertexData = new float[cubeVertexNum * vertexAttribNum];
	for (int i = 0; i < cubeVertexNum; ++i) {
		vertexData[i * vertexAttribNum] = CUBE_VERTEX_DATA(i, PosX) * 1;
		vertexData[i * vertexAttribNum + 1] = CUBE_VERTEX_DATA(i, PosY) * 1;
		vertexData[i * vertexAttribNum + 2] = CUBE_VERTEX_DATA(i, PosZ) * 1;
	}
	indexData = new unsigned int[cubeIndexNum];
	for (int i = 0; i < cubeIndexNum; i++) {
		indexData[i] = CUBE_INDEX_DATA(i);
		/*indexData[i + 1] = CUBE_INDEX_DATA((i + 2));
		indexData[i + 2] = CUBE_INDEX_DATA((i + 1));*/
	}
}
