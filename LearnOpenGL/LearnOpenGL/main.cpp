

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "Config.h"
#include "Shader.h"
#include "GameScene.h"
#include "TextureLoader.h"

void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void update(float deltaTime);
void render();

void debug();

GameScene* gameScene = NULL;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);
	//glDepthMask(GL_FALSE);

	GLSimpleCube::initVertexData();
	GLSimpleLight::initVertexData();
	GLPointLight::initVertexData();
	GLSpotLight::initVertexData();
	GLSimpleMaterial::initVertexData();
	GLLightMapCube::initVertexData();
	GLCubeBorder::initVertexData();
	GLAlphaTexture::initVertexData();
	GLBlendingTexture::initVertexData();
	GLPostProcessingRect::initVertexData();
	GLSkyBox::initVertexData();

	gameScene = new GameScene();
	//gameScene->setPostProcessing("postProcessing.vs", "blur.fs");
	gameScene->setCamera(new Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f)));

	gameScene->setSkyBox(new GLSkyBox("SkyBox/SkyBox1"));

	/*GLLightObject* spotLight = gameScene->addLight(
		new GLSpotLight(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	spotLight->setAmbient(glm::vec3(0.1f));
	spotLight->setDiffuse(glm::vec3(0.5f));
	spotLight->setSpecular(glm::vec3(0.2f));*/


	GLLightObject* dirLight = (GLLightObject*)gameScene->addLight(
		new GLDirectionLight(glm::vec3(-0.2f, -1.0f, -0.3f)));
	dirLight->setAmbient(glm::vec3(0.1f));
	dirLight->setDiffuse(glm::vec3(0.8f));
	dirLight->setSpecular(glm::vec3(0.2f));

	GLLightObject* dirLight2 = (GLLightObject*)gameScene->addLight(
		new GLDirectionLight(glm::vec3(-0.2f, 1.0f, -0.3f)));
	dirLight2->setAmbient(glm::vec3(0.1f));
	dirLight2->setDiffuse(glm::vec3(0.8f));
	dirLight2->setSpecular(glm::vec3(0.2f));

	//GLLightObject* light = (GLLightObject*)gameScene->addLight(
	//	new GLPointLight(glm::vec3(0.0f, 0.0f, 0.0f)));
	//light->setAmbient(glm::vec3(0.3f));
	//light->setDiffuse(glm::vec3(2.8f));
	//light->setSpecular(glm::vec3(0.5f));

	/*GLLightObject* light2 = (GLLightObject*)gameScene->addLight(
		new GLPointLight());
	light2->setAmbient(glm::vec3(0.1f));
	light2->setDiffuse(glm::vec3(0.5f));
	light2->setSpecular(glm::vec3(0.2f));

	GLLightObject* light3 = (GLLightObject*)gameScene->addLight(
		new GLPointLight(glm::vec3(-1.0f, 0.0f, 1.0f)));
	light3->setAmbient(glm::vec3(0.1f));
	light3->setDiffuse(glm::vec3(0.5f));
	light3->setSpecular(glm::vec3(0.2f));*/

	/*GLObject* modelObject = new GLObject("Resource/Model/nanosuit/nanosuit.obj",
		glm::vec3(0.0f, -10.0f, -15.0f));
	modelObject->setShader("lightMap.vs", "lightMap.fs");
	gameScene->addObject(modelObject);*/

	GLObject* reflectionModel = new GLObject("Resource/Model/nanosuit/nanosuit.obj",
		glm::vec3(0.0f, -10.0f, -15.0f));
	reflectionModel->setShader("refraction.vs", "refraction.fs");
	gameScene->addObject(reflectionModel);

	/*GLLightMapCube* lightMapCube = (GLLightMapCube*)gameScene->addObject(
		new GLLightMapCube(glm::vec3(0.0f, 0.0f, -2.0f)));*/

	/*GLAlphaTexture* alphaTexture = (GLAlphaTexture*)gameScene->addObject(new GLAlphaTexture(
		glm::vec3(0.0f,0.0f,-0.2f)));*/

	/*GLBlendingTexture* blendingTexture = (GLBlendingTexture*)gameScene->addObject(new GLBlendingTexture(
		glm::vec3(0.0f, 0.0f, -0.2f)));

	GLBlendingTexture* blendingTexture2 = (GLBlendingTexture*)gameScene->addObject(new GLBlendingTexture(
		glm::vec3(0.5f, 0.5f, -0.3f)));

	GLBlendingTexture* blendingTexture3 = (GLBlendingTexture*)gameScene->addObject(new GLBlendingTexture(
		glm::vec3(-0.5f, -0.5f, -0.4f)));*/

	//GLLightMapCube* lightMapCube2 = (GLLightMapCube*)gameScene->addObject(
	//	new GLLightMapCube(glm::vec3(1.2f, 0.0f, 0.0f)));

	//GLLightMapCube* lightMapCube3 = (GLLightMapCube*)gameScene->addObject(
	//	new GLLightMapCube(glm::vec3(-1.2f, 0.0f, 0.0f)));

	//GLFrameCube* frameCube = (GLFrameCube*)gameScene->addObject(new GLFrameCube(glm::vec3(1.0f, 1.0f, 1.0f)));
	//GLFrameCube* frameCube2 = (GLFrameCube*)gameScene->addObject(new GLFrameCube(glm::vec3(2.2f, 1.5f, 0.7f)));
	//GLFrameCube* frameCube3 = (GLFrameCube*)gameScene->addObject(new GLFrameCube(glm::vec3(4.2f, 2.5f, -0.7f)));

	//GLCubeBorder* border = (GLCubeBorder*)gameScene->addObject(new GLCubeBorder());

	/*GLSimpleMaterial* material = (GLSimpleMaterial*)gameScene->addObject(
		new GLSimpleMaterial(glm::vec3(0.0f, -1.0f, 0.0f)));
	material->setMaterial(Material(
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		glm::vec3(1.0f, 0.5f, 0.31f),
		32.0f
	));*/
	/*gameScene->addObject(new GLSimpleCube(glm::vec3(-5.0f, 1.0f, 0.0f)));
	gameScene->addObject(new GLSimpleCube(glm::vec3(1.0f, 1.0f, 0.0f)));*/
	gameScene->start();

	double timeLast = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double timeCurr = glfwGetTime();
		double deltaTime = timeCurr - timeLast;

		processInput(window);	
		update(deltaTime);
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		timeLast = timeCurr;
	}

	delete gameScene;

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double posX, double posY) {
	gameScene->handleMouseMove(posX, posY);
}

void processInput(GLFWwindow* window) {
	gameScene->handleKeyInput(window);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		debug();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void printVec3(std::string name, glm::vec3 vec) {
	std::cout << name << " " << vec.x << " " << vec.y << " " << vec.z << std::endl;
}

void debug() {

}

void update(float timeDelta) {
	gameScene->update(timeDelta);
}

void render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	gameScene->render();
}

