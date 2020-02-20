#pragma once

#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Config.h"
#include "Shader.h"
#include "TextureLoader.h"


class GLObject {
public:
	GLObject();
	~GLObject();
	virtual void start();
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
	virtual void update(float deltaTime);
protected:
	unsigned int VAO, VBO, EBO;
	Shader* shader = NULL;
};

#endif