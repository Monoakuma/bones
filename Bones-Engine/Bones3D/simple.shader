#shader vertex
#version 410 core

layout(location = 0) in vec3 position;
//layout(location = 1) in vec4 incolor;
//varying vec4 fragColor;


void main()
{
	gl_Position = vec4(position, 1.0);
	//fragColor = incolor;
};


#shader fragment
#version 410 core

layout(location = 0) out vec4 color;
uniform vec4 uColor;
//varying vec4 fragColor;
void main()
{
	color = uColor;
	//color = vec4(1.0, 0.5, 1.0, 1.0);
};