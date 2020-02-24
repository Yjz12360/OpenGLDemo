#include "GLLightObject.h"

GLLightObject::GLLightObject(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
	:GLObject(translation, rotation, scale)
{
}

Light GLLightObject::getLight()
{
	return light;
}

glm::vec3 GLLightObject::getAmbient()
{
	return light.ambient;
}

glm::vec3 GLLightObject::getDiffuse()
{
	return light.diffuse;
}

glm::vec3 GLLightObject::getSpecular()
{
	return light.specular;
}

void GLLightObject::setLight(Light light)
{
	this->light = light;
}

void GLLightObject::setAmbient(glm::vec3 ambient)
{
	light.ambient = ambient;
}

void GLLightObject::setDiffuse(glm::vec3 diffuse)
{
	light.diffuse = diffuse;
}

void GLLightObject::setSpecular(glm::vec3 specular)
{
	light.specular = specular;
}
