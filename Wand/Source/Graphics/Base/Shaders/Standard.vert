#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoords;
layout(location = 3) in float texSlot;
layout(location = 4) in float isText;
out vec4 vColor;
out vec2 vTexCoords;
out float vTexSlot;
out float vIsText;

uniform mat4 uProjection;

void main()
{
	gl_Position = uProjection * vec4(position, 1.0);
	vColor = color;
	vTexCoords = texCoords;
	vTexSlot = texSlot;
	vIsText = isText;
}
