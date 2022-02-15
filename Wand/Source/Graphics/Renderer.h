#pragma once

#include "Base/VertexArray.h"
#include "Base/VertexBuffer.h"
#include "Base/IndexBuffer.h"
#include "Base/ShaderProgram.h"
#include "Drawable.h"


namespace wand
{
	class Renderer
	{
	public:
		static void Init();
		static void Render();

		static void Draw(Drawable* drawable);

	private:
		// Variables
		static std::unique_ptr<VertexArray> sVAO;
		static std::unique_ptr<VertexBuffer> sVBO;
		static std::unique_ptr<IndexBuffer> sIBO;
		static std::unique_ptr<ShaderProgram> sProgram;
		static std::vector<Drawable*> sRenderQueue;
		static std::array<int, MAX_TEXTURES> sSavedTexSlots;

		// Functions
		static void SetupBuffers();
		static void SetupShaderProgram();
		static void SaveTextureSlot(Drawable* sprite, unsigned int& slotIndex);
		static void FillVertexBuffer(unsigned int& drawablesInBuffer, unsigned int& itemsInBuffer);
	};
}
