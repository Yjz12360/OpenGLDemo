#include "GameScene.h"

GameScene::GameScene()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		objects[i] = NULL;
	}
	camera = NULL;
}

GameScene::~GameScene()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] != NULL) {
			delete objects[i];
		}
	}
	if (camera != NULL) {
		delete camera;
	}
}

void GameScene::addObject(GLObject * object)
{
	int index = getAvailObjIndex();
	if (index == -1)return;
	objects[index] = object;
}

void GameScene::setCamera(Camera * camera)
{
	this->camera = camera;
}

Camera * GameScene::getCamera()
{
	return camera;
}

void GameScene::start()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] != NULL) {
			objects[i]->start();
		}
	}
}

void GameScene::update(float deltaTime)
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] != NULL) {
			objects[i]->update(deltaTime);
		}
	}
}

void GameScene::render()
{
	render(camera->getViewMatrix(), camera->getProjMatrix());
}

void GameScene::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] != NULL) {
			objects[i]->render(viewMatrix, projMatrix);
		}
	}
}

void GameScene::handleKeyInput(GLFWwindow* window)
{
	if (camera != NULL) {
		float cameraSpeed = 0.0005f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->moveFront(cameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->moveBack(cameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->moveLeft(cameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->moveRight(cameraSpeed);
	}
}

void GameScene::handleMouseMove(double mouseX, double mouseY)
{
	static double lastX = mouseX;
	static double lastY = mouseY;

	double offsetX = mouseX - lastX;
	double offsetY = mouseY - lastY;

	float cameraSensitivity = 0.05f;
	camera->turnRight(offsetX * cameraSensitivity);
	camera->turnUp(offsetY * cameraSensitivity);

	lastX = mouseX;
	lastY = mouseY;
}

int GameScene::getAvailObjIndex()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] == NULL) {
			return i;
		}
	}
	return -1;
}

