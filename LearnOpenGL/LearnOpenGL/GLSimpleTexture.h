#pragma once

#ifndef GL_SIMPLE_TEXTURE_H
#define GL_SIMPLE_TEXTURE_H

#include "GLObject.h"

static float texVertices[] = {
	 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 2.0f,
	 0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 2.0f, 0.0f,
	-0.5f,-0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f
};

static unsigned int texIndices[] = {
	0,1,3,
	1,2,3
};

class GLSimpleTexture : public GLObject {
public:
	GLSimpleTexture() {
		

		TextureLoader::setWrap(GL_MIRRORED_REPEAT);
		TextureLoader::loadTexture(texture1, "tex3.jpg");
		TextureLoader::setWrap(GL_REPEAT);
		TextureLoader::loadTexture(texture2, "tex2.jpg");

		glBufferData(GL_ARRAY_BUFFER, sizeof(texVertices), texVertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(texIndices), texIndices, GL_STATIC_DRAW);
	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		shader = new Shader("simpleTex.vs", "simpleTex.fs");
	}
	virtual void start() {
		GLObject::start();

		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::scale(trans, glm::vec3(1.5, 1.5, 1.5));
	}

	virtual void render() {
		GLObject::render();

		shader->setMatrix4("transform", trans);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		shader->setInt("textureA", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		shader->setInt("textureB", 1);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	virtual void update(float deltaTime) {
		GLObject::update(deltaTime);

		trans = glm::rotate(trans, glm::radians(90.0f * deltaTime), 
			glm::vec3(0.0, 0.0, 1.0));
	}

private:
	unsigned int texture1, texture2;
	glm::mat4 trans;
};

#endif
