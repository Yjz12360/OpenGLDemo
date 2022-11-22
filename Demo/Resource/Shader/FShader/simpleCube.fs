#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D textureA;
uniform sampler2D textureB;

void main()
{
	FragColor = mix(texture(textureA, TexCoord), texture(textureB, TexCoord), 0.2);
}