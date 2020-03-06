#include "GLMovingCube.h"

GLMovingCube::GLMovingCube(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLLightMapCube(translation, rotation, scale)
{
}

void GLMovingCube::update(float deltaTime)
{
	static float timeTotal = 0.0f;
	timeTotal += deltaTime;

	rotateX(deltaTime * 1.3f);
	rotateY(deltaTime * 1.1f);
	rotateZ(deltaTime * 1.7f);

}
