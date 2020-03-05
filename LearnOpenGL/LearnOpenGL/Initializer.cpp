#include "Initializer.h"

void Initializer::initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilMask(0xFF);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);

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
}
