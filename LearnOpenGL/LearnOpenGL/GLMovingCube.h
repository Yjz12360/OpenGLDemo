#pragma once

#include "GLObject.h"
#include "GLLightMapCube.h"

class GLMovingCube : public GLLightMapCube {
public:
	GLMovingCube(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);

	virtual void update(float deltaTime);
};