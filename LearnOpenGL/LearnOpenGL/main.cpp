

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "Config.h"
#include "Shader.h"
#include "DemoGameScene.h"
#include "TextureLoader.h"
#include "Initializer.h"

void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(GLFWwindow* window);

void debug();

DemoGameScene* gameScene = NULL;

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

	Initializer::initialize();

	gameScene = new DemoGameScene();
	gameScene->initScene();
	gameScene->start();

	double timeLast = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double timeCurr = glfwGetTime();
		double deltaTime = timeCurr - timeLast;

		processInput(window);	
		gameScene->update(deltaTime);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		gameScene->render();

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

void debug() {

}

