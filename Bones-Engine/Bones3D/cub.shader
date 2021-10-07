
#shader vertex
#version 330 core
// Uniforms
// ------------------------------------
uniform   mat4 u_model;
uniform   mat4 u_view;
uniform   mat4 u_projection;
uniform   vec4 u_color;

// Attributes
// ------------------------------------
attribute vec3 a_position;
attribute vec4 a_color;
//attribute vec3 a_normal;

// Varying
// ------------------------------------
varying vec4 v_color;

void main()
{
	v_color = a_color * u_color;
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
#shader fragment
#version 330 core
// Varying
// ------------------------------------
varying vec4 v_color;

void main()
{
	gl_FragColor = v_color;
}