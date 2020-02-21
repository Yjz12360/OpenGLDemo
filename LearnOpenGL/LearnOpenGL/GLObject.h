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
	/*GLObject();*/
	GLObject(glm::vec3 translation = defaultTranslation,
		glm::vec3 rotation = defaultRotation,
		glm::vec3 scale = defaultScale);
	~GLObject();
	virtual void start();
	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
	virtual void update(float deltaTime);

	void translate(glm::vec3 offset);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void scale(float scale);
protected:
	unsigned int VAO, VBO, EBO;
	Shader* shader = NULL;

	glm::vec3 translation = glm::vec3();
	glm::vec3 rotation = glm::vec3();
	glm::vec3 scaleVec = glm::vec3();

	const static glm::vec3 defaultTranslation;
	const static glm::vec3 defaultRotation;
	const static glm::vec3 defaultScale;
private:
	glm::mat4 getModelMatrix();

};

#endif