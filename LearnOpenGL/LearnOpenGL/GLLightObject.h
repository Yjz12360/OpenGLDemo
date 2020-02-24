#pragma once

#ifndef GL_LIGHT_OBJECT_H
#define GL_LIGHT_OBJECT_H

#include "GLObject.h"
#include "Light.h"


class GLLightObject : public GLObject {
public:
	GLLightObject(glm::vec3 translation = GLObject::defaultTranslation,
		glm::vec3 rotation = GLObject::defaultRotation,
		glm::vec3 scale = GLObject::defaultScale);

	Light getLight();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	void setLight(Light light);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
private:
	Light light;
};

#endif
