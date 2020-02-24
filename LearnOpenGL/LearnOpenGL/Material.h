#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;

	Material() :
		ambient(glm::vec3(1.0f)),
		diffuse(glm::vec3(1.0f)),
		specular(glm::vec3(1.0f)),
		shininess(32.0f) {};
	Material(glm::vec3 ambient, glm::vec3 diffuse,
		glm::vec3 specular, float shininess) :
		ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		shininess(shininess) {};
};
