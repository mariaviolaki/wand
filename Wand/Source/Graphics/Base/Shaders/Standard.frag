#version 330 core

in vec4 vColor;
in vec2 vTexCoords;
in float vTexSlot;
in float vIsText;
out vec4 color;

uniform sampler2D uTexSlots[16];
uniform float uPixelRange;

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
    if (vIsText == 0.0)
    {
        color = texture(uTexSlots[int(vTexSlot)], vTexCoords) * vColor;
    }
    else
    {
        vec3 msd = texture(uTexSlots[int(vTexSlot)], vTexCoords).rgb;
        float sd = median(msd.r, msd.g, msd.b);
        float screenPxDistance = uPixelRange * (sd - 0.5);
        float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
        color = vec4(1.0, 1.0, 1.0, opacity) * vColor;
    }
};
