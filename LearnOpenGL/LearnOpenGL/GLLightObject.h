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

	virtual LightType getLightType() = 0;
	virtual const Light* getLight() = 0;
	virtual glm::vec3 getAmbient() = 0;
	virtual glm::vec3 getDiffuse() = 0;
	virtual glm::vec3 getSpecular() = 0;
	virtual void setAmbient(glm::vec3 ambient) = 0;
	virtual void setDiffuse(glm::vec3 diffuse) = 0;
	virtual void setSpecular(glm::vec3 specular) = 0;
};

#endif
