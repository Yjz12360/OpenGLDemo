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
	setShaderUniform();
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] == NULL) continue;
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
		float cameraSpeed = 0.001f;
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

void GameScene::setShaderUniform()
{
	int lightCount = 0;
	GLLightObject* currLights[MAX_LIGHT_NUM];
	int shaderLightIndex[MAX_LIGHT_NUM];
	int dir = 0, point = 0, spot = 0;
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] == NULL) continue;
		if (lights[i]->getLight() == NULL) continue;
		currLights[lightCount] = lights[i];
		switch (lights[i]->getLightType()) {
		case Point:shaderLightIndex[lightCount] = point++; break;
		case Direction:shaderLightIndex[lightCount] = dir++; break;
		case Spot:shaderLightIndex[lightCount] = spot++; break;
		}
		lightCount++;
	}
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] == NULL || (!objects[i]->getShader())) continue;
		objects[i]->getShader()->use();
		objects[i]->getShader()->setVec3("viewPos", getCamera()->getPos());
		for (int j = 0; j < lightCount; ++j) {
			std::string attrName = "";
			LightType lightType = currLights[j]->getLightType();
			switch (lightType) {
			case Point:attrName = "pointLights"; break;
			case Direction: attrName = "dirLights"; break;
			case Spot:attrName = "spotLights"; break;
			}
			char cIndex = shaderLightIndex[j] + '0';
			std::string sIndex = std::string("[").append(1, cIndex).append("]");

			std::string sLightAmbient = attrName + sIndex + ".ambient";
			objects[i]->getShader()->setVec3(sLightAmbient, currLights[j]->getAmbient());
			std::string sLightDiffuse = attrName + sIndex + ".diffuse";
			objects[i]->getShader()->setVec3(sLightDiffuse, currLights[j]->getDiffuse());
			std::string sLightSpecular = attrName + sIndex + ".specular";
			objects[i]->getShader()->setVec3(sLightSpecular, currLights[j]->getSpecular());

			if (lightType == Point) {
				std::string sLightPos = attrName + sIndex + ".position";
				objects[i]->getShader()->setVec3(sLightPos, currLights[j]->getTranslation());
				std::string sLightConstant = attrName + sIndex + ".constant";
				objects[i]->getShader()->setFloat(sLightConstant, 
					((PointLight*)currLights[j]->getLight())->constant);
				std::string sLightLinear = attrName + sIndex + ".linear";
				objects[i]->getShader()->setFloat(sLightLinear,
					((PointLight*)currLights[j]->getLight())->linear);

				std::string sLightQuadratic = attrName + sIndex + ".quadratic";
				objects[i]->getShader()->setFloat(sLightQuadratic,
					((PointLight*)currLights[j]->getLight())->quadratic);

			}
			else if (lightType == Direction) {
				std::string sLightDirection = attrName + sIndex + ".direction";
				objects[i]->getShader()->setVec3(sLightDirection,
					((DirectionLight*)currLights[j]->getLight())->direction);
				glm::vec3 d = ((DirectionLight*)currLights[j]->getLight())->direction;
			}
			else if (lightType == Spot) {
				//...
			}
		}
		objects[i]->getShader()->setInt("pointLightNum", point);
		objects[i]->getShader()->setInt("dirLightNum", dir);
	}
}

