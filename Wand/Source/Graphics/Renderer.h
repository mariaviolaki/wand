#pragma once

#include "Base/VertexArray.h"
#include "Base/VertexBuffer.h"
#include "Base/IndexBuffer.h"
#include "Base/ShaderProgram.h"
#include "Drawable.h"
#include "UI/UIEntity.h"

namespace wand
{
	class Renderer
	{
	public:
		Renderer();

		void Init(float windowWidth, float windowHeight);
		void ResetProjectionMatrix(float xMin, float yMin, float xMax, float yMax);
		void Submit(std::vector<std::unique_ptr<UIEntity>>& entities);

	private:
		// Variables
		std::unique_ptr<VertexArray> mVAO;
		std::unique_ptr<VertexBuffer> mVBO;
		std::unique_ptr<IndexBuffer> mIBO;
		std::unique_ptr<ShaderProgram> mShaderProgram;
		std::array<int, MAX_TEXTURES> mSavedTexSlots;
		std::vector<Drawable*> mRenderQueue;

		// Private Methods
		void SetupBuffers();
		void SetupShaderProgram(float windowWidth, float windowHeight);
		void SaveTextureSlot(Drawable* sprite, unsigned int& slotIndex);
		void FillVertexBuffer(unsigned int& drawablesInBuffer, unsigned int& itemsInBuffer);
		void Render();
	};
}
