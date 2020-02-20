#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Config.h"

class Camera {
public:
	Camera();
	Camera(glm::vec3 pos, glm::vec3 target);
	Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up);

	void moveFront(float offset);
	void moveBack(float offset);
	void moveUp(float offset);
	void moveDown(float offset);
	void moveLeft(float offset);
	void moveRight(float offset);

	void turnLeft(float angle);
	void turnRight(float angle);
	void turnUp(float angle);
	void turnDown(float angle);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraLeft;
	glm::vec3 cameraUp;
};

#endif
