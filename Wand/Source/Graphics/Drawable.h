#pragma once

#include "Graphics.h"
#include "Transform.h"
#include "Base/Texture.h"

namespace wand
{
	class Drawable
	{
	protected:
		Drawable(glm::vec4 color);
		Drawable(const std::string& imagePath);

	public:
		static unsigned int GetIndexCount();
		static unsigned int GetSize();

		// Transform operations
		glm::vec3 GetPosition() const;
		float GetWidth() const;
		float GetHeight() const;
		void SetPosition(float x, float y);
		void SetWidth(float width);
		void SetHeight(float height);

		// Drawable operations
		unsigned int GetTexId() const;
		glm::vec4 GetColor() const;
		virtual void SetColor(glm::vec4 color);
		virtual void SetTextureSlot(int slot);
		std::array<Vertex, 4>* GetVertexData();

	private:
		static const unsigned int sIndexCount;
		static const unsigned int sSize;

		glm::vec4 mColor;
		std::shared_ptr<Transform> mTransform;
		std::shared_ptr<Texture> mTexture;
		std::shared_ptr<std::array<Vertex, 4>> mVertices;
	};
}
