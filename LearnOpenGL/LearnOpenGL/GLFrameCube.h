#pragma once

#include "GLObject.h"
#include "GLLightMapCube.h"
#include "GLCubeBorder.h"

class GLFrameCube :public GLLightMapCube {
public:
	GLFrameCube(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);

	virtual void start();
	virtual void update(float deltaTime);
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
private:
	GLCubeBorder border;
};