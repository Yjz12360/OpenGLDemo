#include "GLObject.h"

const glm::vec3 GLObject::defaultTranslation = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 GLObject::defaultRotation = glm::vec3(0.0f, 0.0f, 0.0f);
const glm::vec3 GLObject::defaultScale = glm::vec3(1.0f, 1.0f, 1.0f);

//GLObject::GLObject()
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//}

GLObject::GLObject(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
{
	this->translation = translation;
	this->rotation = rotation;
	this->scaleVec = scale;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

GLObject::~GLObject()
{
	if (shader != NULL) {
		delete shader;
	}
}

void GLObject::start()
{
}

void GLObject::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	if (shader != NULL) {
		shader->use();
		shader->setMatrix4("model", getModelMatrix());
		shader->setMatrix4("view", viewMatrix);
		shader->setMatrix4("projection", projMatrix);
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void GLObject::update(float deltaTime)
{
}

void GLObject::translate(glm::vec3 offset)
{
	translation += offset;
}

void GLObject::rotateX(float angle)
{
	rotation.x += glm::radians(angle);
}

void GLObject::rotateY(float angle)
{
	rotation.y += glm::radians(angle);
}

void GLObject::rotateZ(float angle)
{
	rotation.z += glm::radians(angle);
}

void GLObject::scale(float scale)
{
	scaleVec = glm::vec3(scale, scale, scale);
}

glm::mat4 GLObject::getModelMatrix()
{
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::scale(mat, scaleVec);
	mat = glm::rotate(mat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	mat = glm::rotate(mat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	mat = glm::rotate(mat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	mat = glm::translate(mat, translation);
	return mat;
}
