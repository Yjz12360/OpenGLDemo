#pragma once

#include "BaseGameScene.h"

class DemoGameScene :public BaseGameScene {
public:
	virtual void initScene();
	virtual void handleKeyInput(GLFWwindow* window);
};