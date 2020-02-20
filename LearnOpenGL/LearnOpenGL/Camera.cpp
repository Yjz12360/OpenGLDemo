#include "Camera.h"

Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraLeft = glm::vec3(1.0f, 0.0f, 0.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(glm::vec3 pos, glm::vec3 target):
	cameraPos(pos)
{
	cameraFront = glm::normalize(target - pos);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraLeft = glm::normalize(glm::cross(up, cameraFront));
	cameraUp = glm::cross(cameraFront, cameraLeft);
}

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up):
	cameraPos(pos)
{
	cameraFront = glm::normalize(target - pos);
	cameraUp = glm::normalize(up);
	cameraLeft = glm::cross(cameraUp, cameraFront);
}

void Camera::moveFront(float offset)
{
	cameraPos += cameraFront * offset;
}

void Camera::moveBack(float offset)
{
	cameraPos -= cameraFront * offset;
}

void Camera::moveUp(float offset)
{
	cameraPos += cameraUp * offset;
}

void Camera::moveDown(float offset)
{
	cameraPos -= cameraUp * offset;
}

void Camera::moveLeft(float offset)
{
	cameraPos += cameraLeft * offset;
}

void Camera::moveRight(float offset)
{
	cameraPos -= cameraLeft * offset;
}

void Camera::turnLeft(float angle)
{
	makeRotation(glm::rotate(glm::mat4(), glm::radians(angle), cameraUp));
}

void Camera::turnRight(float angle)
{
	makeRotation(glm::rotate(glm::mat4(), glm::radians(-angle), cameraUp));

}

void Camera::turnUp(float angle)
{
	makeRotation(glm::rotate(glm::mat4(), glm::radians(angle), cameraLeft));

}

void Camera::turnDown(float angle)
{
	makeRotation(glm::rotate(glm::mat4(), glm::radians(-angle), cameraLeft));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4 Camera::getProjMatrix()
{
	return glm::perspective(glm::radians(45.0f), 1.0f * SRC_WIDTH / SRC_HEIGHT, 0.1f, 100.0f);
}

void Camera::makeRotation(glm::mat4 rotation)
{
	glm::vec4 front = glm::vec4(cameraFront, 1.0f);
	front = rotation * front;
	cameraFront.x = front.x;
	cameraFront.y = front.y;
	cameraFront.z = front.z;
	cameraLeft = glm::normalize(glm::vec3(front.z, 0.0f, -front.x));
	cameraUp = glm::cross(cameraFront, cameraLeft);
}
