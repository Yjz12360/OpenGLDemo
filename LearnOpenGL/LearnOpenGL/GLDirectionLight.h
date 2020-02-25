#pragma once

#ifndef GL_DIRECTION_LIGHT_H
#define GL_DIRECTION_LIGHT_H

#include "GLLightObject.h"
#include "Light.h"

class GLDirectionLight : public GLLightObject {
public:
	GLDirectionLight();
	GLDirectionLight(glm::vec3 direction);

	virtual void render(glm::vec3 viewMatrix, glm::vec3 projMatrix);

	virtual LightType getLightType();
	virtual const Light* getLight();
	virtual glm::vec3 getAmbient();
	virtual glm::vec3 getDiffuse();
	virtual glm::vec3 getSpecular();
	virtual void setAmbient(glm::vec3 ambient);
	virtual void setDiffuse(glm::vec3 diffuse);
	virtual void setSpecular(glm::vec3 specular);
private:
	DirectionLight light;
};

#endif
