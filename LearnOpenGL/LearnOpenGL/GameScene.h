#pragma once

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<string.h>

#include "Camera.h"
#include "GLObject.h"
#include "GLLightObject.h"
#include "GLDirectionLight.h"
#include "GLPointLight.h"
#include "GLSimpleCube.h"
#include "GLSimpleLight.h"
#include "GLSimpleMaterial.h"
#include "GLSimpleTexture.h"
#include "GLLightMapCube.h"

const unsigned int MAX_OBJECT_NUM = 100;
const unsigned int MAX_CAMERA_NUM = 3;
const unsigned int MAX_LIGHT_NUM = 3;

class GameScene {
public:
	GameScene();
	~GameScene();

	GLObject* addObject(GLObject* object);
	GLLightObject* addLight(GLLightObject* light);

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
	int getAvailLightIndex();

	void setShaderUniform();


	Camera* camera;
	GLObject* objects[MAX_OBJECT_NUM];
	GLLightObject* lights[MAX_LIGHT_NUM];
};


#endif
