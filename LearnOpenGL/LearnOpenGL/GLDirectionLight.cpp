#include "GLDirectionLight.h"

GLDirectionLight::GLDirectionLight()
{
}

GLDirectionLight::GLDirectionLight(glm::vec3 direction)
{
	light.direction = glm::normalize(direction);
}

void GLDirectionLight::render(glm::vec3 viewMatrix, glm::vec3 projMatrix)
{
}

LightType GLDirectionLight::getLightType()
{
	return Direction;
}

const Light * GLDirectionLight::getLight()
{
	return &light;
}

glm::vec3 GLDirectionLight::getAmbient()
{
	return light.ambient;
}

glm::vec3 GLDirectionLight::getDiffuse()
{
	return light.diffuse;
}

glm::vec3 GLDirectionLight::getSpecular()
{
	return light.specular;
}

void GLDirectionLight::setAmbient(glm::vec3 ambient)
{
	light.ambient = ambient;
}

void GLDirectionLight::setDiffuse(glm::vec3 diffuse)
{
	light.diffuse = diffuse;
}

void GLDirectionLight::setSpecular(glm::vec3 specular)
{
	light.specular = specular;
}
