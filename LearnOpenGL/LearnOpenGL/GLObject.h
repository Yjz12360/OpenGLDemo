#pragma once

#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "TextureLoader.h"


class GLObject {
public:
	GLObject() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}
	~GLObject() {
		if (shader != NULL) {
			delete shader;
		}
	}
	virtual void start() {
		
	}
	virtual void render() {
		if (shader != NULL) {
			shader->use();
		}
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	};
	virtual void update(float deltaTime) {

	}
	
protected:

	unsigned int VAO, VBO, EBO;
	Shader* shader = NULL;
};

#endif