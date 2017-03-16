#version 400

	layout(location=0) in vec3 position;
	layout(location=1) in vec3 normal;
	layout(location=2) in vec2 textCoord;
	layout (location = 3) in vec3 tangent;
	layout (location = 4) in vec3 bitangent;

	out vec3 FragPos;
	out vec3 Normal;
	out vec2 TextCoord;
	//out vec4 FragPosLightSpace;

	uniform mat4 transform;
	uniform mat4 view;
	uniform mat4 projection;
	//uniform mat4 lightSpaceMatrix;

	void main(void)
	{
		gl_Position = projection * view * transform * vec4(position,1.0f);

		FragPos = vec3(transform * vec4(position, 1.0f));
		Normal= mat3(transpose(inverse(transform))) * normal;
		TextCoord=textCoord;
		//FragPosLightSpace= lightSpaceMatrix * vec4(FragPos,1.0);
	}