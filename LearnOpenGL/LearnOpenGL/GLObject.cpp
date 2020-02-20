#include "GLObject.h"

GLObject::GLObject()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

GLObject::~GLObject()
{
	if (shader != NULL) {
		delete shader;
	}
}

void GLObject::start()
{
}

void GLObject::render()
{
	if (shader != NULL) {
		shader->use();
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void GLObject::update(float deltaTime)
{
}
