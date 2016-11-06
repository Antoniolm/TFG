#version 330 core
out vec4 color;

in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
color= vec4(lightColor * objectColor, 1.0f);
}