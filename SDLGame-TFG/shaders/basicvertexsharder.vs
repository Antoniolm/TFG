#version 400

	layout(location=0) in vec3 position;

	uniform mat4 transform;
	uniform mat4 view;
	uniform mat4 projection;

	void main(void)
	{
		gl_Position = projection * view * transform * vec4(position,1.0f);
	}