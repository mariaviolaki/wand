#version 330 core

in vec4 vColor;
in vec2 vTexCoords;
in float vTexSlot;
in float vIsText;
out vec4 color;

uniform sampler2D uTexSlots[16];

void main()
{
    if (vIsText == 0.0)
    {
        color = texture(uTexSlots[int(vTexSlot)], vTexCoords) * vColor;
    }
    else
    {
        color = vec4(vColor.rgb, texture(uTexSlots[int(vTexSlot)], vTexCoords).r * vColor.a);
    }
};
