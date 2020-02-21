#pragma once

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "GLObject.h"
#include "GLSimpleCube.h"

const unsigned int MAX_OBJECT_NUM = 100;

class GameScene {
public:
	GameScene();
	~GameScene();

	void addObject(GLObject* object);

	void start();
	void update(float deltaTime);
	void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
private:
	int getAvailableIndex();

	GLObject* objects[MAX_OBJECT_NUM];

};

#endif
