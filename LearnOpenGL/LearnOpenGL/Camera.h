#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera();
	Camera(glm::mat4 pos, glm::mat4 target);
	Camera(glm::mat4 pos, glm::mat4 target, glm::mat4 up);
	void moveUp(float offset);
	void moveDown(float offset);
	void moveLeft(float offset);
	void moveRight(float offset);

	void turnLeft(float angle);
	void turnRight(float angle);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
};

#endif
