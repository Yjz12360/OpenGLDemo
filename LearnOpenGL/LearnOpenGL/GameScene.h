#pragma once

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "Camera.h"
#include "GLObject.h"
#include "GLSimpleCube.h"

const unsigned int MAX_OBJECT_NUM = 100;
const unsigned int MAX_CAMERA_NUM = 3;

class GameScene {
public:
	GameScene();
	~GameScene();

	void addObject(GLObject* object);
	void setCamera(Camera* camera);
	Camera* getCamera();

	void start();
	void update(float deltaTime);
	void render();
	void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);

	void handleKeyInput(GLFWwindow* window);
	void handleMouseMove(double mouseX, double mouseY);
private:
	int getAvailObjIndex();

	Camera* camera;
	GLObject* objects[MAX_OBJECT_NUM];

	
};


#endif
