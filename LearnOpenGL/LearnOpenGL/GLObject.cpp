#include "GLObject.h"

const glm::vec3 GLObject::defaultTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 GLObject::defaultRotation = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 GLObject::defaultScale = glm::vec3(1.0f, 1.0f, 1.0f);

GLObject::GLObject(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

GLObject::GLObject(const char * modelPath, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, translation);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	

	loadModel(modelPath);
}

GLObject::~GLObject()
{
	if (shader != NULL) {
		delete shader;
	}
	if (model != NULL) {
		delete model;
	}
}

void GLObject::start()
{
}

void GLObject::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if (shader != NULL) {
		shader->use();
		shader->setMatrix4("model", modelMatrix);
		shader->setMatrix4("view", viewMatrix);
		shader->setMatrix4("projection", projMatrix);

		if (model != NULL) {
			shader->setFloat("material.shininess", 64.0f);
			model->Draw(*shader);
		}
	}

	if (model == NULL) {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

}

void GLObject::update(float deltaTime)
{
}

void GLObject::translate(glm::vec3 offset)
{
	modelMatrix = glm::translate(modelMatrix, offset);
}

void GLObject::rotateX(float angle)
{
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(1.0f, 0.0f, 0.0f));
}

void GLObject::rotateY(float angle)
{
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void GLObject::rotateZ(float angle)
{
	modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
}

void GLObject::scale(float scale)
{
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
}

void GLObject::lookAt(glm::vec3 direction)
{
	glm::vec3 pos = getTranslation();
	modelMatrix = glm::lookAt(pos, pos + direction, glm::vec3(0.0f, 1.0f, 0.0f));
}

void GLObject::loadModel(const char * path)
{
	if (model != NULL) {
		delete model;
	}
	model = new Model((char*)path);
}

glm::vec3 GLObject::getTranslation()
{
	return glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
	//return glm::vec3(modelMatrix[0][3], modelMatrix[1][3], modelMatrix[2][3]);
}

void GLObject::setShader(const char * vsPath, const char * fsPath)
{
	if (shader != NULL) {
		delete shader;
		shader = NULL;
	}
	if (vsPath == "" || fsPath == "") {
		return;
	}
	shader = new Shader(vsPath, fsPath);
}

Shader * GLObject::getShader()
{
	return shader;
}
