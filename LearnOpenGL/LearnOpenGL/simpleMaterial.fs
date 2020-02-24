#version 330 core
out vec4 FragColor;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 viewPos;
//uniform vec3 lightPos1;
//uniform vec3 lightColor1;
uniform Material material;
uniform Light light1;

void main()
{
	vec3 ambient = light1.ambient * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light1.position - FragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = light1.diffuse * diff * material.diffuse;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
	vec3 specular = light1.specular * (material.specular * spec);

	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}