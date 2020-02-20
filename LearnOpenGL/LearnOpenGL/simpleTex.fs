#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D textureA;
uniform sampler2D textureB;

void main()
{
	vec2 revTexCoord;
	revTexCoord.x = 1.0 - TexCoord.x;
	revTexCoord.y = 1.0 - TexCoord.y;
	FragColor = mix(texture(textureA, TexCoord), texture(textureB, revTexCoord), 0.2);
}