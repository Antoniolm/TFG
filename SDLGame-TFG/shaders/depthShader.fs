#version 330 core
//out vec4 color;
//in vec2 TexCoords;

layout(location = 0) out float fragmentdepth;

//uniform sampler2D depthMap;

void main()
{       
	fragmentdepth = gl_FragCoord.z;      
}  