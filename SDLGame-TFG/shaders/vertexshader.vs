#version 400

	layout(location=0) in vec3 position;
	layout (location=1) in vec3 normal;

	out vec3 FragPos;
	out vec3 Normal;

	uniform mat4 transform;
	uniform mat4 view;
	uniform mat4 projection;

	void main(void)
	{
		gl_Position = projection * view * transform * vec4(position,1.0f);

		FragPos = vec3(transform * vec4(position, 1.0f));
		Normal= mat3(transpose(inverse(transform))) * normal;
	}