#pragma once

#ifndef GL_SIMPLE_RECT_H
#define GL_SIMPLE_RECT_H

#include "GLObject.h"

class GLSimpleRect : public GLObject {
public:
	GLSimpleRect();
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
};
#endif