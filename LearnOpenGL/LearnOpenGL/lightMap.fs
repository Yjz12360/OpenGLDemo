#version 330 core
out vec4 FragColor;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform Material material;
uniform Light light1;

void main()
{
	vec3 ambient = light1.ambient * texture(material.diffuse, TexCoords).rgb;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light1.position - FragPos);
	float diff = max(dot(norm, lightDir),0.0);
	vec3 diffuse = light1.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
	vec3 specular = light1.specular * spec * texture(material.specular, TexCoords).rgb;

	vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}