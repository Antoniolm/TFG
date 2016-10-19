#version 400

	layout(location=0) in vec3 in_Position;
	layout(location=1) in vec4 in_Color;
	out vec4 ex_Color;

	uniform mat4 transform;

	mat4 m = mat4(
   		1.0, 0.0, 0.0,0.0, 
   		0.0, 1.0, 0.0,0.0, 
   		0.0, 0.0, 1.0,0.0, 
   		0.2, -0.5, 0.0,1.0
	);

	void main(void)
	{
		gl_Position = transform * vec4(in_Position,1.0f);
		ex_Color = in_Color;
	}