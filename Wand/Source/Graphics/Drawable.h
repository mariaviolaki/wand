#pragma once

#include "Graphics.h"
#include "glm/glm.hpp"

namespace wand
{
	class Drawable
	{
	public:
		static unsigned int GetIndexCount();
		static unsigned int GetSize();

		Drawable();

		void SetPosition(float x, float y);
		void SetWidth(float width);
		void SetHeight(float height);

		glm::vec3 GetPosition() const;
		float GetWidth() const;
		float GetHeight() const;

		virtual std::array<Vertex, 4>* GetVertexData() { return nullptr; };

	private:
		static const unsigned int sIndexCount;
		static const unsigned int sSize;

		glm::mat4 mTransform;
		float mWidth;
		float mHeight;
	};
}
