#include "WandPCH.h"
#include "Renderer.h"

#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/VertexLayout.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/ShaderProgram.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Graphics.h"
#include "Sprite.h"
#include "Utils.h"

namespace // only accessible from this translation unit
{
	std::unique_ptr<wand::VertexArray> vao;
	std::unique_ptr<wand::VertexBuffer> vbo;
	std::unique_ptr<wand::IndexBuffer> ibo;
	std::unique_ptr<wand::ShaderProgram> program;
	std::vector<wand::Drawable*> renderQueue;
	std::array<int, wand::MAX_TEXTURES> savedTexSlots {-1};

	// Initialize the vao, vbo, and ibo to be used for rendering
	void InitBuffers()
	{
		vao = std::make_unique<wand::VertexArray>();
		// Allocate memory for 1 large vertex and index buffer
		vbo = std::make_unique<wand::VertexBuffer>(nullptr, wand::MAX_VERTICES * sizeof(wand::Vertex));
		ibo = std::make_unique<wand::IndexBuffer>();

		// Create a layout for the vertex array according to the attributes in the Vertex struct
		wand::VertexLayout* layout = new wand::VertexLayout();
		layout->AddFloats(wand::Vertex().position.length()); // vec3(x, y, z) -> 3 floats
		layout->AddFloats(wand::Vertex().color.length()); // vec4(r, g, b, a) -> 4 floats
		layout->AddFloats(wand::Vertex().texCoords.length()); // vec2(x, y) -> 2 floats
		layout->AddFloats(1); // texture slot number -> 1 float
		vao->AddLayout(layout);
	}

	// Initialize the shader program and its uniforms to be used for rendering
	void InitShaderProgram(wand::Window* window)
	{
		// Choose the shaders to be used for rendering
		program = std::make_unique<wand::ShaderProgram>("Standard.vert", "Standard.frag");

		// Set up the texture slots in the fragment shader
		const int slotCount = wand::MAX_TEXTURES + 1; // include the 'no texture' slot
		int texSlots[slotCount];
		for (int i = 0; i < slotCount; i++) texSlots[i] = i;
		program->SetUniform1iv("uTexSlots", slotCount, texSlots);
		// Set the projection matrix in the shader according to the window size
		program->SetUniformMat4("uProjection",
			glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), -1.0f, 1.0f));
	}

	// Save the sprite's texture id in a new texture slot
	void SaveTextureSlot(wand::Drawable* sprite, unsigned int& slotIndex)
	{
		// Get the texture id of the sprite
		unsigned int texId = sprite->GetTexId();
		// Check if the texture already has a slot id
		bool found = wand::Utils::FindInArray(texId, savedTexSlots.data(), savedTexSlots.size()) != -1;
		// Save the slot for the current texture and increase the slot index
		if (!found)
		{
			sprite->SetTextureSlot(slotIndex + 1); // slot 0 = no texture
			savedTexSlots[slotIndex++] = texId;
		}
	}

	// Add up to the maximum number of drawables to the buffer
	unsigned int FillVertexBuffer()
	{
		unsigned int count = 0;
		unsigned int slotIndex = 0;
		// Add drawables from the queue to the vertex buffer
		for (auto& drawable : renderQueue)
		{
			// Check if the drawable is a sprite (instead of a rectangle)
			if (dynamic_cast<wand::Sprite*>(drawable))
				SaveTextureSlot(drawable, slotIndex);

			// Add the drawables data to the large index buffer
			glBufferSubData(GL_ARRAY_BUFFER,
				count * wand::Drawable::GetSize(),	// starting point in buffer
				wand::Drawable::GetSize(),			// size in buffer
				drawable->GetVertexData()->data());	// data to be rendered
			count++;

			if (count == wand::MAX_DRAWABLES || slotIndex == wand::MAX_TEXTURES)
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
		InitBuffers();
		InitShaderProgram(window);
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
			// Reset the texture slots so that they can be reused by new textures
			savedTexSlots.fill(-1);
		}
		while (!renderQueue.empty());
	}
}

/**************************************************************************************/

namespace wand::Renderer // compile with C++17 at least
{
	// Get an already existing drawable and push it to the render queue
	void Draw(Drawable* drawable)
	{
		renderQueue.emplace_back(drawable);
	}
}
