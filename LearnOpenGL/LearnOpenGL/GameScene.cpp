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
	skyBox = NULL;

	offScreen = NULL;
	postProcessing = NULL;
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
	if (skyBox != NULL) {
		delete skyBox;
	}
	if (offScreen != NULL) {
		delete offScreen;
	}
	if (postProcessing != NULL) {
		delete postProcessing;
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

void GameScene::setSkyBox(GLSkyBox * skyBox)
{
	this->skyBox = skyBox;
}

void GameScene::setPostProcessing(const char * vs, const char * fs)
{
	if (offScreen == NULL) {
		offScreen = new OffScreenRenderer();
	}
	if (postProcessing == NULL) {
		postProcessing = new GLPostProcessingRect(vs, fs);
	}
	else {
		postProcessing->setShader(vs, fs);
	}
	
}

void GameScene::start()
{
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] != NULL) {
			objects[i]->start();
		}
	}
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] != NULL) {
			lights[i]->start();
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
	if (offScreen != NULL && postProcessing != NULL && postProcessing->getShader() != NULL) {
		offScreen->setOffScreen(true);
	}

	setShaderUniform();
	map<float, int>sorted = getSortedObjByDistance();
	for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
		if (objects[it->second] == NULL) continue;
		objects[it->second]->render(viewMatrix, projMatrix);
	}
	for (int i = 0; i < MAX_LIGHT_NUM; ++i) {
		if (lights[i] == NULL)  continue;
		lights[i]->render(viewMatrix, projMatrix);
	}
	if (skyBox != NULL) {
		skyBox->render(viewMatrix, projMatrix);
	}

	if (offScreen != NULL && postProcessing != NULL && postProcessing->getShader() != NULL) {
		offScreen->setOffScreen(false);
		postProcessing->setTextureBuffer(offScreen->getTextureBuffer());
		postProcessing->renderPostProcess();
	}
}

void GameScene::handleKeyInput(GLFWwindow* window)
{
	if (camera != NULL) {
		float cameraSpeed = 0.005f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->moveFront(cameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->moveBack(cameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->moveLeft(cameraSpeed);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->moveRight(cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		setPostProcessing("", "");
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		setPostProcessing("postProcessing.vs", "inversion.fs");
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		setPostProcessing("postProcessing.vs", "grayScale.fs");
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		setPostProcessing("postProcessing.vs", "blur.fs");
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		setPostProcessing("postProcessing.vs", "sharpen.fs");
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

map<float, int> GameScene::getSortedObjByDistance()
{
	map<float, int> result;
	for (int i = 0; i < MAX_OBJECT_NUM; ++i) {
		if (objects[i] == NULL)  continue;
		float distance = glm::distance(objects[i]->getTranslation(), camera->getPos());
		result[distance] = i;
	}
	return result;
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
		if (camera != NULL) {
			objects[i]->getShader()->setVec3("viewPos", camera->getPos());
		}
		if (skyBox != NULL) {
			skyBox->addTextureToShader(objects[i]->getShader());
		}
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
			}
			else if (lightType == Spot) {
				std::string sLightPos = attrName + sIndex + ".position";
				objects[i]->getShader()->setVec3(sLightPos,
					currLights[j]->getTranslation());
				glm::vec3 t = currLights[j]->getTranslation();
				std::string sLightDirection = attrName + sIndex + ".direction";
				objects[i]->getShader()->setVec3(sLightDirection,
					((SpotLight*)currLights[j]->getLight())->direction);
				std::string sLightCutOff = attrName + sIndex + ".cutOff";
				objects[i]->getShader()->setFloat(sLightCutOff,
					((SpotLight*)currLights[j]->getLight())->cutOff);
				std::string sLightOutCutOff = attrName + sIndex + ".outerCutOff";
				objects[i]->getShader()->setFloat(sLightOutCutOff,
					((SpotLight*)currLights[j]->getLight())->outerCutOff);
				std::string sLightLinear = attrName + sIndex + ".linear";
				objects[i]->getShader()->setFloat(sLightLinear,
					((SpotLight*)currLights[j]->getLight())->linear);
				std::string sLightQuadratic = attrName + sIndex + ".quadratic";
				objects[i]->getShader()->setFloat(sLightQuadratic,
					((SpotLight*)currLights[j]->getLight())->quadratic);
			}
		}
		objects[i]->getShader()->setInt("pointLightNum", point);
		objects[i]->getShader()->setInt("dirLightNum", dir);
		objects[i]->getShader()->setInt("spotLightNum", spot);
	}
}

