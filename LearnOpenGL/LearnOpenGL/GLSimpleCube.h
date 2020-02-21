#pragma once

#ifndef GL_SIMPLE_CUBE_H
#define GL_SIMPLE_CUBE_H

#include "GLObject.h"

class GLSimpleCube : public GLObject {
public:
	GLSimpleCube(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
private:
	unsigned int texture1, texture2;
};

#endif