#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"

namespace wand
{
	// Define constants
	const unsigned int MAX_RECTS = 1000;
	const unsigned int MAX_VERTICES = MAX_RECTS * 4; // 1 rectangle = 4 vertices
	const unsigned int MAX_INDICES = MAX_RECTS * 6; // 1 rectangle = 2 triangles = 2 * 3 vertices

	// An array of floats to be sent to the GPU
	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
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
