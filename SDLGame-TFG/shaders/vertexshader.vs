#version 400

	layout(location=0) in vec3 in_Position;
	layout(location=1) in vec4 in_Color;
	out vec4 ex_Color;

	uniform mat4 transform;

	void main(void)
	{
		gl_Position = vec4(in_Position,1.0f);
		ex_Color = in_Color;
	}