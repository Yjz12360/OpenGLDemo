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

void GLObject::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if (shader != NULL) {
		shader->use();
		shader->setMatrix4("view", viewMatrix);
		shader->setMatrix4("projection", projMatrix);
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void GLObject::update(float deltaTime)
{
}
