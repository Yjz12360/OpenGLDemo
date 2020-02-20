#pragma once

#ifndef GL_SIMPLE_TEXTURE_H
#define GL_SIMPLE_TEXTURE_H

#include "GLObject.h"

class GLSimpleTexture : public GLObject {
public:
	GLSimpleTexture();
	virtual void start();
	virtual void render();
	virtual void update(float deltaTime);
private:
	unsigned int texture1, texture2;
	glm::mat4 trans;
	glm::mat4 view;
	glm::mat4 projection;
};

#endif
