#include "DemoGameScene.h"

void DemoGameScene::initScene()
{
	setCamera(new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f)));
	setSkyBox(new GLSkyBox("SkyBox/SkyBox1"));

	spotLight = new GLSpotLight();
	spotLight->enabled = false;
	addLight(spotLight);

	GLLightObject* dirLight = new GLDirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f));
	dirLight->setAmbient(glm::vec3(0.3f));
	dirLight->setDiffuse(glm::vec3(0.8f));
	dirLight->setSpecular(glm::vec3(0.5f));
	addLight(dirLight);

	GLLightObject* pointLight = new GLPointLight(glm::vec3(-25.0f,8.0f,0.0f));
	pointLight->setAmbient(glm::vec3(0.3f));
	pointLight->setDiffuse(glm::vec3(0.8f));
	pointLight->setSpecular(glm::vec3(0.5f));
	addLight(pointLight);

	GLObject* reflectionModel = new GLObject("nanosuit/nanosuit.obj",
		glm::vec3(0.0f, -10.0f, 15.0f), glm::vec3(0.0f, glm::radians(180.0f),0.0f));
	reflectionModel->setShader("reflection.vs", "reflection.fs");
	addObject(reflectionModel);

	GLObject* refractionModel = new GLObject("nanosuit/nanosuit.obj",
		glm::vec3(0.0f, -10.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	refractionModel->setShader("refraction.vs", "refraction.fs");
	addObject(refractionModel);

	addObject(new GLLightMapCube(glm::vec3(20.0f, 0.0f, -9.5f), glm::vec3(0.0f), glm::vec3(5.0f)));
	addObject(new GLBlendingTexture(glm::vec3(20.0f, 0.0f, -6.0f), glm::vec3(0.0f), glm::vec3(5.0f)));
	addObject(new GLBlendingTexture(glm::vec3(20.5f, 0.5f, -4.0f), glm::vec3(0.0f), glm::vec3(6.0f)));
	addObject(new GLBlendingTexture(glm::vec3(19.5f, -0.5f, -2.0f), glm::vec3(0.0f), glm::vec3(8.0f)));

	addObject(new GLFrameCube(glm::vec3(-24.0f, 2.5f, -0.7f), glm::vec3(0.0f), glm::vec3(6.0f)));
	addObject(new GLFrameCube(glm::vec3(-20.0f, 6.5f, -5.7f), glm::vec3(1.0f), glm::vec3(6.0f)));
	addObject(new GLFrameCube(glm::vec3(-30.0f, 7.5f, 5.7f), glm::vec3(2.0f), glm::vec3(6.0f)));

	addObject(new GLAlphaTexture(glm::vec3(-30.0f, -1.0f, -30.0f), glm::vec3(0.0f), glm::vec3(6.0f)));
	addObject(new GLAlphaTexture(glm::vec3(-29.0f, -1.0f, -29.0f), glm::vec3(0.0f), glm::vec3(5.5f)));
	addObject(new GLAlphaTexture(glm::vec3(-29.4f, -1.0f, -31.0f), glm::vec3(0.0f), glm::vec3(5.6f)));
	addObject(new GLAlphaTexture(glm::vec3(-31.1f, -1.0f, -30.3f), glm::vec3(0.0f), glm::vec3(5.7f)));
	addObject(new GLAlphaTexture(glm::vec3(-32.1f, -1.0f, -29.3f), glm::vec3(0.0f), glm::vec3(5.8f)));
	addObject(new GLAlphaTexture(glm::vec3(-25.5f, -1.0f, -30.0f), glm::vec3(0.0f), glm::vec3(5.5f)));
	addObject(new GLAlphaTexture(glm::vec3(-24.3f, -1.0f, -29.5f), glm::vec3(0.0f), glm::vec3(5.9f)));
	addObject(new GLAlphaTexture(glm::vec3(-24.8f, -1.0f, -31.6f), glm::vec3(0.0f), glm::vec3(5.9f)));
	addObject(new GLAlphaTexture(glm::vec3(-26.5f, -1.0f, -30.7f), glm::vec3(0.0f), glm::vec3(5.6f)));
	addObject(new GLAlphaTexture(glm::vec3(-27.3f, -1.0f, -29.2f), glm::vec3(0.0f), glm::vec3(5.6f)));
	addObject(new GLAlphaTexture(glm::vec3(-35.5f, -1.0f, -30.0f), glm::vec3(0.0f), glm::vec3(5.5f)));
	addObject(new GLAlphaTexture(glm::vec3(-34.3f, -1.0f, -29.5f), glm::vec3(0.0f), glm::vec3(6.0f)));
	addObject(new GLAlphaTexture(glm::vec3(-34.8f, -1.0f, -31.6f), glm::vec3(0.0f), glm::vec3(5.6f)));
	addObject(new GLAlphaTexture(glm::vec3(-36.5f, -1.0f, -30.7f), glm::vec3(0.0f), glm::vec3(6.1f)));
	addObject(new GLAlphaTexture(glm::vec3(-37.3f, -1.0f, -29.2f), glm::vec3(0.0f), glm::vec3(5.7f)));
	addObject(new GLSimpleCube(glm::vec3(-30.0f, -4.0f, -30.0f),glm::vec3(0.0f),glm::vec3(20.0f,1.0f,20.0f)));

	addObject(new GLMovingCube(glm::vec3(40.0f, -2.0f, -40.0f), glm::vec3(0.0f), glm::vec3(8.0f)));
}

void DemoGameScene::handleKeyInput(GLFWwindow * window)
{
	BaseGameScene::handleKeyInput(window);
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
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		spotLight->enabled = true;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		spotLight->enabled = false;
	updateSpotLightPos();
}

void DemoGameScene::handleMouseMove(double mouseX, double mouseY)
{
	BaseGameScene::handleMouseMove(mouseX, mouseY);
	updateSpotLightPos();
}

void DemoGameScene::updateSpotLightPos()
{
	spotLight->translateTo(getCamera()->getPos());
	((SpotLight*)spotLight->getLight())->direction = getCamera()->getDirection();
}
