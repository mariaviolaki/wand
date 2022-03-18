#pragma once

#include "Base/VertexArray.h"
#include "Base/VertexBuffer.h"
#include "Base/IndexBuffer.h"
#include "Base/ShaderProgram.h"
#include "Drawable.h"
#include "UI/UIComponent.h"


namespace wand
{
	class Renderer
	{
	public:
		Renderer();

		void Render();
		void Submit(std::vector<std::unique_ptr<UIComponent>>& components);

	private:
		// Variables
		std::unique_ptr<VertexArray> mVAO;
		std::unique_ptr<VertexBuffer> mVBO;
		std::unique_ptr<IndexBuffer> mIBO;
		std::unique_ptr<ShaderProgram> mShaderProgram;
		std::array<int, MAX_TEXTURES> mSavedTexSlots;
		std::vector<Drawable*> mRenderQueue;

		// Functions
		void Init();
		void SetupBuffers();
		void SetupShaderProgram();
		void SaveTextureSlot(Drawable* sprite, unsigned int& slotIndex);
		void FillVertexBuffer(unsigned int& drawablesInBuffer, unsigned int& itemsInBuffer);
	};
}
