#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "Shader.h"
#include "Rect2DVertexData.h"
#include "Config.h"

class OffScreenRenderer {
public:
	OffScreenRenderer();
	GLuint getTextureBuffer();
	void setOffScreen(bool offScreen);

private:
	GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil);

	Shader* shader = NULL;
	GLuint frameBuffer;
	GLuint textureColorBuffer;
	GLuint rbo;
};