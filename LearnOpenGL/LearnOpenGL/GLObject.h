#pragma once

#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Config.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "Model.h"

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

	void lookAt(glm::vec3 direction);

	void loadModel(const char* path);

	glm::vec3 getTranslation();

	void setShader(const char* vsPath, const char* fsPath);
	Shader* getShader();
protected:
	unsigned int VAO, VBO, EBO;
	Shader* shader = NULL;

	const static glm::vec3 defaultTranslation;
	const static glm::vec3 defaultRotation;
	const static glm::vec3 defaultScale;
private:
	glm::mat4 modelMatrix;
	Model* model = NULL;
};

#endif