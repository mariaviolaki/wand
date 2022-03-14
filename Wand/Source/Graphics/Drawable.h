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
		bool IsVisible() const;
		void Show();
		void Hide();

		virtual unsigned int GetItemCount() const = 0;
		virtual unsigned int GetBufferSize() const = 0;
		virtual const std::vector<Vertex>& GetVertexData() = 0;

		virtual unsigned int GetTexId() const { return 0; };
		virtual void SetTextureSlot(int slot) {};
		virtual glm::vec4 GetColor() const { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
		virtual void SetColor(glm::vec4 color) {};

		// Transform operations
		std::shared_ptr<Transform> GetGFXTransform() const;
		glm::vec2 GetPosition() const;
		float GetDepth() const;
		float GetWidth() const;
		float GetHeight() const;
		void SetPosition(float x, float y);
		void SetDepth(float depth);
		void SetWidth(float width);
		void SetHeight(float height);

	private:
		static const unsigned int sIndexCount;
		bool mIsVisible;
		std::shared_ptr<Transform> mTransform;
	};
}
