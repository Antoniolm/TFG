#version 400

	layout(location=0) in vec3 in_Position;
	layout(location=1) in vec4 in_Color;
	out vec4 ex_Color;

	uniform mat4 transform;
	uniform mat4 view;
	uniform mat4 projection;

	void main(void)
	{
		gl_Position = projection * view * transform *vec4(in_Position,1.0f);
		ex_Color = in_Color;
	}