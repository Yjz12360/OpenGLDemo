

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "Shader.h"
#include "GLSimpleRect.h"
#include "GLSimpleTexture.h"
#include "TextureLoader.h"

void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height);
void processInput(GLFWwindow* window);
void start();
void update(float deltaTime);
void render();

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;

GLSimpleRect* rect = NULL;
GLSimpleTexture* texture = NULL;

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
	
	TextureLoader::init();

	rect = new GLSimpleRect();
	texture = new GLSimpleTexture();

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

	delete rect;
	delete texture;

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* WINDOW, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void start() {
	rect->start();
	texture->start();
}

void update(float timeDelta) {
	rect->update(timeDelta);
	texture->update(timeDelta);
}

void render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	rect->render();
	texture->render();
}

