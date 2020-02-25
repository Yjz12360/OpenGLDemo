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

struct DirectionLight :Light {
	glm::vec3 direction;
	DirectionLight() :Light(), direction(glm::vec3(-1.0f, -1.0f, -1.0f)) {};
	DirectionLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		glm::vec3 dir) :Light(ambient, diffuse, specular), direction(dir) {};
};

struct SpotLight :Light {
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;
	SpotLight() :Light() {
		direction = glm::vec3(0.0f, 0.0f, -1.0f);
		cutOff = glm::cos(glm::radians(12.5f));
		outerCutOff = glm::cos(glm::radians(15.0f));
		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;
	}
	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		glm::vec3 dir) : Light(ambient, diffuse, specular), direction(dir) {
		direction = glm::vec3(0.0f, 0.0f, -1.0f);
		cutOff = glm::cos(glm::radians(12.5f));
		outerCutOff = glm::cos(glm::radians(15.0f));
		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;
	}
	SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		glm::vec3 dir, float cutOff, float outCutOff, float constant,
		float linear, float quadratic) :
		Light(ambient, diffuse, specular),
		direction(dir),
		cutOff(cutOff),
		outerCutOff(outCutOff),
		constant(constant),
		linear(linear),
		quadratic(quadratic) {};

};