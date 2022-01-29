#pragma once

#include "glm/glm.hpp"

namespace wand
{
	// Define constants
	const unsigned short MAX_DRAWABLES = 1000;
	const unsigned short MAX_VERTICES = MAX_DRAWABLES * 4; // 1 drawable = 4 vertices
	const unsigned short MAX_INDICES = MAX_DRAWABLES * 6; // 1 drawable = 2 triangles = 2 * 3 vertices
	const unsigned char MAX_TEXTURES = 15; // 1st slot = no texture

	// An array of floats to be sent to the GPU
	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoords;
		float texSlot;
	};

	// Contains information about the data in a single vertex attribute
	struct VertexAttribute
	{
		unsigned int count;
		unsigned int type;
		unsigned int normalized;
		unsigned int offset;
	};
}
