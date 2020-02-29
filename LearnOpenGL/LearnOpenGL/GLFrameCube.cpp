#include "GLFrameCube.h"

GLFrameCube::GLFrameCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLLightMapCube(translation, rotation, scale),
	border(translation, rotation, scale)
{
}

void GLFrameCube::start()
{
	GLLightMapCube::start();
	border.start();
}

void GLFrameCube::update(float deltaTime)
{
	GLLightMapCube::update(deltaTime);
	border.update(deltaTime);
}

void GLFrameCube::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	
	glStencilFunc(GL_ALWAYS, 0x01, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	GLLightMapCube::render(viewMatrix, projMatrix);

	border.render(viewMatrix, projMatrix);
}
