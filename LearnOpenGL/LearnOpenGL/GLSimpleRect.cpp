#include "GLSimpleRect.h"

static float vertices[] = {
	 0.6f, 0.8f, 0.0f, 0.0f, 1.0f, 1.0f,
	 0.8f, 0.8f, 0.0f, 1.0f, 1.0f, 0.0f,
	 0.8f, 0.6f, 0.0f, 1.0f, 1.0f, 1.0f,
	 0.6f, 0.6f, 0.0f, 1.0f, 0.0f, 1.0f
};

static unsigned int indices[] = {
	0,1,3,
	1,2,3
};

GLSimpleRect::GLSimpleRect()
{
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	shader = new Shader("shader.vs", "shader.fs");
}

void GLSimpleRect::render()
{
	GLObject::render();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
