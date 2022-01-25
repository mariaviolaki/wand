#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
out vec4 vColor;

uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * vec4(position, 1.0);
	vColor = color;	
}
