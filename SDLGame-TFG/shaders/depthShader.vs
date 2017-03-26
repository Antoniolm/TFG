#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 lightSpaceMatrix;
uniform mat4 transform;

void main()
{
    gl_Position = lightSpaceMatrix * transform * vec4(position, 1.0f);
}  