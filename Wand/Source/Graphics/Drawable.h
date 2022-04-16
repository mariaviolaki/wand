#pragma once

#include "Graphics.h"
#include "Base/Transform.h"

namespace wand
{
	class Drawable
	{
	protected:
		Drawable();

	public:
		static unsigned int GetIndexCount();

		// Drawable operations
		std::shared_ptr<Transform> GetTransform() const;

		virtual unsigned int GetItemCount() const = 0;
		virtual unsigned int GetBufferSize() const = 0;
		virtual const std::vector<Vertex>& GetVertexData() = 0;

		virtual unsigned int GetTexId() const { return 0; };
		virtual void SetTextureSlot(int slot) {};
		virtual glm::vec4 GetColor() const { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
		virtual void SetColor(glm::vec4 color) {};

	protected:
		static const unsigned int sIndexCount;
		std::shared_ptr<Transform> mTransform;
	};
}
