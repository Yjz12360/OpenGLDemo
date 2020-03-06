#include "GLSimpleTexture.h"

static float texVertices[] = {
	 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f,
	 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 2.0f, 0.0f,
	-0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f
};

static unsigned int texIndices[] = {
	0,1,3,
	1,2,3
};

GLSimpleTexture::GLSimpleTexture()
{
	TextureLoader::setWrap(GL_MIRRORED_REPEAT);
	TextureLoader::loadTexture(texture1, "untitled.png");
	TextureLoader::setWrap(GL_REPEAT);
	TextureLoader::loadTexture(texture2, "untitled.png");

	glBufferData(GL_ARRAY_BUFFER, sizeof(texVertices), texVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texIndices), texIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	shader = new Shader("simpleTex.vs", "simpleTex.fs");
}

void GLSimpleTexture::start()
{
	GLObject::start();
	scale(1.5f);
}

void GLSimpleTexture::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	GLObject::render(viewMatrix, projMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	shader->setInt("textureA", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	shader->setInt("textureB", 1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void GLSimpleTexture::update(float deltaTime)
{
	GLObject::update(deltaTime);

}
