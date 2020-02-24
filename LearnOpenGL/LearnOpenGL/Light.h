#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

enum LightType { Direction, Point, Spot };

struct Light {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light() :ambient(glm::vec3(1.0f)),
		diffuse(glm::vec3(1.0f)), specular(glm::vec3(1.0f)) {}
	Light(glm::vec3 ambient, glm::vec3 diffuse,
		glm::vec3 specular) :
		ambient(ambient),
		diffuse(diffuse),
		specular(specular) {};
};

struct PointLight : Light{
	float constant;
	float linear;
	float quadratic;
	PointLight() :Light(),constant(1.0f),linear(0.14f),quadratic(0.07f) {};
	PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float radius) :Light(ambient, diffuse, specular) {
		constant = 1.0f;
		linear = 0.14f;
		quadratic = 0.07f;
	}
};

