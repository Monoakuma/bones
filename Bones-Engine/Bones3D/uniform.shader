#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

void main()
{
	gl_Position = vec4(position, 1.0);
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform float uTime;
void main()
{
	color = vec4(abs(sin(uTime)), abs(sin(uTime-1)), abs(sin(uTime-2)),1.0f);
};