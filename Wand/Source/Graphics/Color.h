#pragma once
#include "glm/glm.hpp"

namespace wand
{
	class Color
	{
	public:
		// Constructor for an RGBA color
		Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

		// Get a vector of integer color values ranging from 0 to 255
		glm::uvec4 GetRGBA() const;
		// Get a vector of float color values ranging from 0 to 1
		glm::vec4 GetBase() const;

		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int a;
	};
}
