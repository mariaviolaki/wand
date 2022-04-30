#pragma once

#include "Graphics.h"
#include "Base/Transform.h"

namespace wand
{
	enum class LayoutPosition
	{
		LEFT, CENTERX, RIGHT, // horizontal
		BOTTOM, CENTERY, TOP  // vertical
	};

	struct ParentLayoutPos
	{
		LayoutPosition horizontal;
		LayoutPosition vertical;
	};

	struct ParentLayoutCoords
	{
		float x;
		float y;
	};

	class Drawable
	{
	public:
		static unsigned int GetIndexCount();

		// Drawable operations
		Transform* GetTransform() const;
		void SetTransform(bool isLayoutChild);
		const Transform* GetParentTransform() const;
		void SetParentTransform(Transform* transform);
		void SetParentLayoutPos(LayoutPosition horizontal, LayoutPosition vertical);
		void SetParentLayoutCoords(float x, float y);

		virtual unsigned int GetItemCount() const = 0;
		virtual unsigned int GetBufferSize() const = 0;
		virtual const std::vector<Vertex>& GetVertexData() = 0;

		virtual unsigned int GetTexId() const { return 0; };
		virtual void SetTextureSlot(int slot) {};
		virtual glm::vec4 GetColor() const { return { 1.0f, 1.0f, 1.0f, 1.0f }; };
		virtual void SetColor(glm::vec4 color) {};

	protected:
		static const unsigned int sIndexCount;
		std::unique_ptr<Transform> mTransform;
		Transform* mParentTransform;

		Drawable();
		void UpdateTransform(bool adoptDimens = false);

	private:
		std::unique_ptr<ParentLayoutPos> mParentLayoutPos;
		std::unique_ptr<ParentLayoutCoords> mParentLayoutCoords;

		void SetParentLayoutPos();
	};
}
