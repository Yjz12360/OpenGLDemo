#pragma once

#ifndef GL_SPOTLIGHT_OBJECT_H
#define GL_SPOTLIGHT_OBJECT_H

#include"GLLightObject.h"
#include"CubeVertexData.h"

class GLSpotLightObject : public GLLightObject {
public:
	GLSpotLightObject(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);

	virtual void render(glm::mat4 viewMatrix, glm::mat4 projMatrix);
	static void initVertexData();

	virtual LightType getLightType();
	virtual const Light* getLight();
	virtual glm::vec3 getAmbient();
	virtual glm::vec3 getDiffuse();
	virtual glm::vec3 getSpecular();
	virtual void setAmbient(glm::vec3 ambient);
	virtual void setDiffuse(glm::vec3 diffuse);
	virtual void setSpecular(glm::vec3 specular);

private:
	const static unsigned int vertexNum = cubeVertexNum;
	const static unsigned int vertexAttribNum = 3;
	const static unsigned int vertexDataSize = sizeof(float) * vertexNum * vertexAttribNum;
	const static unsigned int indexNum = cubeIndexNum;
	const static unsigned int indexDataSize = sizeof(unsigned int) * indexNum;

	static float* vertexData;
	static unsigned int* indexData;

	SpotLight light;
};

#endif
