#version 330 core

in vec4 vColor;
in vec2 vTexCoords;
in float vTexSlot;
out vec4 color;

uniform sampler2D uTexSlots[16];

void main()
{
	color = texture(uTexSlots[int(vTexSlot)], vTexCoords) * vColor;
};
