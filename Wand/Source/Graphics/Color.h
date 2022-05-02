#pragma once
#include "glm/glm.hpp"

namespace wand
{
	class Color
	{
	public:
		// Constructor for an RGBA color
		Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

		glm::uvec4 GetRGBA() const;
		glm::vec4 GetBase() const;

		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int a;
	};
}
