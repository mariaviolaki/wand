#include "WandPCH.h"
#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Graphics.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace // only accessible from this translation unit
{
	std::unique_ptr<wand::VertexArray> vao;
	std::unique_ptr<wand::VertexBuffer> vbo;
	std::unique_ptr<wand::IndexBuffer> ibo;
	std::unique_ptr<wand::ShaderProgram> program;
	std::vector<std::shared_ptr<wand::Drawable>> renderQueue;

	// Add up to the maximum number of drawables to the buffer
	unsigned int FillVertexBuffer()
	{
		unsigned int count = 0;
		// Add drawables from the queue to the vertex buffer
		for (auto& drawable : renderQueue)
		{
			// Add the drawables data to the large index buffer
			glBufferSubData(GL_ARRAY_BUFFER,
				count * wand::Drawable::GetSize(),	// starting point in buffer
				wand::Drawable::GetSize(),			// size in buffer
				drawable.get()->GetVertexData()->data());	// data to be rendered
			count++;

			if (count == wand::MAX_DRAWABLES)
				break;
		}
		return count;
	}
}

/**************************************************************************************/

namespace wand::RenderManager // compile with C++17 at least
{
	void Init(Window* window)
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
		// Set the projection matrix in the shader according to the window size
		program.get()->SetUniformMat4("u_Projection", 
			glm::ortho(0.0f, (float) window->GetWidth(), 0.0f, (float) window->GetHeight(), -1.0f, 1.0f));
	}

	void Render()
	{
		do
		{
			// Render each drawable in the vertex buffer
			unsigned int drawablesInBuffer = FillVertexBuffer();
			glDrawElements(
				GL_TRIANGLES, Drawable::GetIndexCount() * drawablesInBuffer, GL_UNSIGNED_INT, nullptr);

			// Remove from the queue the drawables that were just rendered
			renderQueue.erase(renderQueue.begin(), renderQueue.begin() + drawablesInBuffer);
		}
		while (!renderQueue.empty());
	}
}

/**************************************************************************************/

namespace wand::Renderer // compile with C++17 at least
{
	// Get an already existing drawable and push it to the render queue
	void Draw(std::shared_ptr<Drawable> drawable)
	{
		renderQueue.emplace_back(drawable);
	}
}
