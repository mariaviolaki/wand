#pragma once

#include "Graphics.h"
#include "Base/Transform.h"

namespace wand
{
	class Drawable
	{
	protected:
		Drawable(glm::vec2 dimens = {100.0f, 100.0f});

	public:
		static unsigned int GetIndexCount();

		// Transform operations
		glm::vec3 GetPosition() const;
		float GetWidth() const;
		float GetHeight() const;
		void SetPosition(float x, float y);
		void SetWidth(float width);
		void SetHeight(float height);

		// Drawable operations
		virtual glm::vec4 GetColor() const { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
		virtual unsigned int GetTexId() const { return 0; };
		virtual void SetColor(glm::vec4 color) {};
		virtual void SetTextureSlot(int slot) {};
		virtual unsigned int GetItemCount() const = 0;
		virtual unsigned int GetBufferSize() const = 0;
		virtual const std::vector<Vertex>& GetVertexData() = 0;

	private:
		static const unsigned int sIndexCount;
		std::shared_ptr<Transform> mTransform;
	};
}
