#include "WandPCH.h"
#include "Color.h"

namespace wand
{
	Color::Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha)
		: r(red), g(green), b(blue), a(alpha)
	{}

	glm::uvec4 Color::GetRGBA() const { return { r, g, b, a}; }
	glm::vec4 Color::GetBase() const { return { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }; }
}
