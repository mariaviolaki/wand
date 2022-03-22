#include "WandPCH.h"
#include "Renderer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Base/VertexLayout.h"
#include "Core/Window.h"
#include "Graphics.h"
#include "SpriteGFX.h"
#include "TextGFX.h"
#include "Utils/Utils.h"

namespace wand
{
	Renderer::Renderer()
		: mVAO(nullptr), mVBO(nullptr), mIBO(nullptr), mShaderProgram(nullptr),
		mSavedTexSlots(), mRenderQueue()
	{
		Init();
	}

	// Get an already existing drawable and push it to the render queue
	void Renderer::Submit(std::vector<std::unique_ptr<UIComponent>>& components)
	{
		for (const auto& component : components)
		{
			if (component->IsVisible())
				mRenderQueue.emplace_back(component->GetDrawable());
		}

		// Sort components based on their depth by providing a comparison function
		std::sort(mRenderQueue.begin(), mRenderQueue.end(),
			[](const Drawable* a, const Drawable* b)
			{
				// Sort in descending order
				return a->GetTransform()->GetDepth() < b->GetTransform()->GetDepth();
			});

		Render();
	}

	// Render all the drawables in the render queue
	void Renderer::Render()
	{
		do
		{
			unsigned int drawablesInBuffer, itemsInBuffer;
			// Reset the texture slots so that they can be reused by new textures
			mSavedTexSlots.fill(-1);
			// Render each drawable in the vertex buffer
			FillVertexBuffer(drawablesInBuffer, itemsInBuffer);
			glDrawElements(
				GL_TRIANGLES, Drawable::GetIndexCount() * itemsInBuffer, GL_UNSIGNED_INT, nullptr);

			// Remove from the queue the drawables that were just rendered
			mRenderQueue.erase(mRenderQueue.begin(), mRenderQueue.begin() + drawablesInBuffer);
		}
		while (!mRenderQueue.empty());
	}

	/********************************** PRIVATE ****************************************/

	void Renderer::Init()
	{
		SetupBuffers();
		SetupShaderProgram();
	}

	// Initialize the vao, vbo, and ibo to be used for rendering
	void Renderer::SetupBuffers()
	{
		mVAO = std::make_unique<VertexArray>();
		// Allocate memory for 1 large vertex and index buffer
		mVBO = std::make_unique<VertexBuffer>(nullptr, MAX_VERTICES * sizeof(Vertex));
		mIBO = std::make_unique<IndexBuffer>();
		
		// Create a layout for the vertex array according to the attributes in the Vertex struct
		VertexLayout* layout = new VertexLayout();
		layout->AddFloats(Vertex().position.length()); // vec3(x, y, z) -> 3 floats
		layout->AddFloats(Vertex().color.length()); // vec4(r, g, b, a) -> 4 floats
		layout->AddFloats(Vertex().texCoords.length()); // vec2(x, y) -> 2 floats
		layout->AddFloats(1); // texture slot number -> 1 float
		layout->AddFloats(1); // to be rendered as text or not -> 1 float
		mVAO->AddLayout(layout);
	}

	// Initialize the shader program and its uniforms to be used for rendering
	void Renderer::SetupShaderProgram()
	{
		// Choose the shaders to be used for rendering
		mShaderProgram = std::make_unique<ShaderProgram>("Standard.vert", "Standard.frag");
		
		// Set up the texture slots in the fragment shader
		const int slotCount = MAX_TEXTURES + 1; // include the 'no texture' slot
		int texSlots[slotCount];
		for (int i = 0; i < slotCount; i++) texSlots[i] = i;
		mShaderProgram->SetUniform1iv("uTexSlots", slotCount, texSlots);
		// Set the projection matrix in the shader according to the window size
		mShaderProgram->SetUniformMat4("uProjection",
			glm::ortho(0.0f, (float)Window::GetWidth(), 0.0f, (float)Window::GetHeight(), -1000.0f, 1000.0f));
	}

	// Save the drawable's texture id in a new texture slot
	void Renderer::SaveTextureSlot(Drawable* drawable, unsigned int& slotIndex)
	{
		// Get the texture id of the drawable
		unsigned int texId = drawable->GetTexId();
		// Check if the texture already has a slot id
		bool found = Utils::FindInArray(texId, mSavedTexSlots.data(), mSavedTexSlots.size()) != -1;
		// Save the slot for the current texture and increase the slot index
		if (!found)
		{
			drawable->SetTextureSlot(slotIndex + 1); // slot 0 = no texture
			mSavedTexSlots[slotIndex++] = texId;
		}
	}

	// Add up to the maximum number of drawables to the buffer
	void Renderer::FillVertexBuffer(unsigned int& drawablesInBuffer, unsigned int& itemsInBuffer)
	{
		unsigned int drawableCount = 0; // number of drawables from the render queue
		unsigned int itemCount = 0; // 1 drawable may include multiple items (text includes letters)
		unsigned int bufferIndex = 0; // first available byte in the vertex buffer
		unsigned int slotIndex = 0;
		// Add drawables from the queue to the vertex buffer
		for (auto& drawable : mRenderQueue)
		{
			if (itemCount + drawable->GetItemCount() > MAX_DRAWABLE_ITEMS || slotIndex == MAX_TEXTURES)
				break;

			// Check if the drawable is a sprite or text object (instead of a rectangle)
			if (dynamic_cast<SpriteGFX*>(drawable) || dynamic_cast<TextGFX*>(drawable))
				SaveTextureSlot(drawable, slotIndex);

			// Add the drawable's data to the large index buffer
			glBufferSubData(GL_ARRAY_BUFFER,
				bufferIndex,						// starting point in buffer
				drawable->GetBufferSize(),			// size in buffer
				&(drawable->GetVertexData()[0]));	// data to be rendered
			drawableCount++;
			itemCount += drawable->GetItemCount();
			bufferIndex += drawable->GetBufferSize();
		}
		drawablesInBuffer = drawableCount;
		itemsInBuffer = itemCount;
	}
}
