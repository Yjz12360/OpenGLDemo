#include "GameScene.h"

GameScene::GameScene()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		objects[i] = NULL;
	}
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		lights[i] = NULL;
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
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] != NULL) {
			delete lights[i];
		}
	}
	if (camera != NULL) {
		delete camera;
	}
}

GLObject* GameScene::addObject(GLObject * object)
{
	int index = getAvailObjIndex();
	if (index == -1) {
		delete object;
		return NULL;
	}
	objects[index] = object;
	return object;
}

GLLightObject * GameScene::addLight(GLLightObject * light)
{
	int index = getAvailLightIndex();
	if (index == -1) {
		delete light;
		return NULL;
	}
	lights[index] = light;
	return light;
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
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] != NULL) {
			lights[i]->update(deltaTime);
		}
	}
}

void GameScene::render()
{
	render(camera->getViewMatrix(), camera->getProjMatrix());
}

void GameScene::render(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	int lightCount = 0;
	glm::vec3 lightPos[MAX_LIGHT_NUM];
	Light lightColor[MAX_LIGHT_NUM];
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] == NULL) continue;
		lightPos[lightCount] = lights[i]->getTranslation();
		lightColor[lightCount] = lights[i]->getLight();
		lightCount++;
	}
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] == NULL || (!objects[i]->getShader())) continue;
		objects[i]->getShader()->use();
		objects[i]->getShader()->setVec3("viewPos", getCamera()->getPos());
		for (int j = 0; j < lightCount; ++j) {
			char cIndex = (j + 1) + '0';
			std::string sLightPos = std::string("light").
				append(1, cIndex).append(".position");
			objects[i]->getShader()->setVec3(sLightPos, lightPos[j]);
			std::string sLightAmbient = std::string("light").
				append(1, cIndex).append(".ambient");
			objects[i]->getShader()->setVec3(sLightAmbient, lightColor[j].ambient);
			std::string sLightDiffuse = std::string("light").
				append(1, cIndex).append(".diffuse");
			objects[i]->getShader()->setVec3(sLightDiffuse, lightColor[j].diffuse);
			std::string sLightSpecular = std::string("light").
				append(1, cIndex).append(".specular");
			objects[i]->getShader()->setVec3(sLightSpecular, lightColor[j].specular);
		}
		objects[i]->render(viewMatrix, projMatrix);
	}
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] == NULL)  continue;
		lights[i]->render(viewMatrix, projMatrix);
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

int GameScene::getAvailLightIndex()
{
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] == NULL) {
			return i;
		}
	}
	return -1;
}

