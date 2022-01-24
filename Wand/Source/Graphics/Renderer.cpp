#include "WandPCH.h"
#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "IndexBuffer.h"
#include "Rectangle.h"
#include "ShaderProgram.h"
#include "Graphics.h"

namespace // only accessible from this translation unit
{
	std::unique_ptr<wand::VertexArray> vao;
	std::unique_ptr<wand::VertexBuffer> vbo;
	std::unique_ptr<wand::IndexBuffer> ibo;
	std::unique_ptr<wand::ShaderProgram> program;
	std::vector<std::unique_ptr<wand::Rectangle>> renderQueue;

	// Add up to the maximum number of rectangles to the buffer
	unsigned int FillVertexBuffer()
	{
		unsigned int count = 0;
		// Add rectangles from the queue to the vertex buffer
		for (const auto& rect : renderQueue)
		{
			// Add the rectangle data to the large index buffer
			glBufferSubData(GL_ARRAY_BUFFER,
				count * wand::Rectangle::GetSize(),	// starting point in buffer
				wand::Rectangle::GetSize(),			// size in buffer
				rect.get()->GetVertexData());		// data to be rendered
			count++;

			if (count == wand::MAX_RECTS)
				break;
		}
		return count;
	}
}

/**************************************************************************************/

namespace wand::RenderManager // compile with C++17 at least
{
	void Init()
	{
		vao = std::make_unique<VertexArray>();
		// Allocate memory for 1 large vertex and index buffer
		vbo = std::make_unique<VertexBuffer>(nullptr, MAX_VERTICES * sizeof(Vertex));
		ibo = std::make_unique<IndexBuffer>();

		// Create a layout for the vertex array according to the attributes in the Vertex struct
		VertexLayout* layout = new VertexLayout();
		layout->AddFloats(Vertex().position.length()); // vec3(x, y, z) -> 3 floats
		layout->AddFloats(Vertex().color.length()); // vec4(r, g, b, a) -> 4 floats
		vao.get()->AddLayout(layout);

		// Choose the shaders to be used for rendering
		program = std::make_unique<ShaderProgram>("Standard.vert", "Standard.frag");
	}

	void Render()
	{
		do
		{
			// Render each rectangle in the vertex buffer
			unsigned int rectsInBuffer = FillVertexBuffer();
			glDrawElements(
				GL_TRIANGLES, Rectangle::GetIndexCount() * rectsInBuffer, GL_UNSIGNED_INT, nullptr);

			// Remove from the queue the rectangles that were just rendered
			renderQueue.erase(renderQueue.begin(), renderQueue.begin() + rectsInBuffer);
		}
		while (!renderQueue.empty());
	}
}

/**************************************************************************************/

namespace wand::Renderer // compile with C++17 at least
{
	void DrawRect(glm::vec2 pos, glm::vec2 dimens, glm::vec4 color)
	{
		// Generate the rectangle to use for rendering and push it to the render queue
		renderQueue.push_back(std::make_unique<Rectangle>(pos, dimens, color));
	}
}
