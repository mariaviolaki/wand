#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"

namespace wand
{
	// Define constants
	const unsigned int MAX_DRAWABLES = 1000;
	const unsigned int MAX_VERTICES = MAX_DRAWABLES * 4; // 1 drawable = 4 vertices
	const unsigned int MAX_INDICES = MAX_DRAWABLES * 6; // 1 drawable = 2 triangles = 2 * 3 vertices

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
