

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "Config.h"
#include "Shader.h"
#include "Camera.h"
#include "GameScene.h"
#include "GLSimpleRect.h"
#include "GLSimpleTexture.h"
#include "GLSimpleCube.h"
#include "TextureLoader.h"

void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);
void start();
void update(float deltaTime);
void render();

void debug();

Camera* camera = NULL;
GameScene* gameScene = NULL;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
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

	glViewport(0, 0, SRC_WIDTH, SRC_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	glEnable(GL_DEPTH_TEST);

	TextureLoader::init();

	glm::vec3 pos = glm::vec3(0.0f, 0.0f, -3.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	camera = new Camera(pos, target);
	gameScene = new GameScene();
	gameScene->addObject(new GLSimpleCube());
	gameScene->addObject(new GLSimpleCube(glm::vec3(1.0f, 1.0f, 0.0f)));

	start();

	double timeLast = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double timeValue = glfwGetTime();

		processInput(window);	
		update(timeValue - timeLast);
		render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		timeLast = timeValue;
	}

	delete camera;

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double posX, double posY) {
	static double lastX = posX;
	static double lastY = posY;

	double offsetX = posX - lastX;
	double offsetY = posY - lastY;


	float sensitivity = 0.05f;
	camera->turnRight(offsetX * sensitivity);
	camera->turnUp(offsetY * sensitivity);

	lastX = posX;
	lastY = posY;
}

void processInput(GLFWwindow* window) {
	float cameraSpeed = 0.0005f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFront(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveBack(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveLeft(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRight(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		debug();
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void start() {
	gameScene->start();
}

void printVec3(std::string name, glm::vec3 vec) {
	std::cout << name << " " << vec.x << " " << vec.y << " " << vec.z << std::endl;
}

void debug() {
	printVec3("cameraPos", camera->cameraPos);
	printVec3("camreaFront", camera->cameraFront);
	printVec3("cameraRight", camera->cameraLeft);
	printVec3("cameraUp", camera->cameraUp);
}

void update(float timeDelta) {
	gameScene->update(timeDelta);
}

void render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto view = camera->getViewMatrix();
	auto proj = camera->getProjMatrix();
	gameScene->render(view, proj);
}

