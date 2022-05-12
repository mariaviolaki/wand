#pragma once

#include "Graphics.h"
#include "Base/Transform.h"
#include "Color.h"

namespace wand
{
	enum class LayoutPosition
	{
		LEFT, MIDLEFT, MIDDLEX, MIDRIGHT, RIGHT, // horizontal
		BOTTOM, MIDBOTTOM, MIDDLEY, MIDTOP, TOP  // vertical
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

		/* Transform operations */
		Transform* GetTransform() const;
		const Transform* GetParentTransform() const;
		void SetParentTransform(Transform* transform);
		void SetParentLayoutPos(LayoutPosition horizontal, LayoutPosition vertical);
		void SetParentLayoutCoords(float x, float y);
		/* Operations used for rendering */
		virtual unsigned int GetItemCount() const = 0;
		virtual unsigned int GetBufferSize() const = 0;
		virtual const std::vector<Vertex>& GetVertexData() = 0;
		virtual unsigned int GetTexId() const { return 0; };
		virtual void SetTextureSlot(int slot) {};
		virtual Color GetColor() const { return Color(255, 255, 255, 0); };
		virtual void SetColor(Color color) {};

	protected:
		static const unsigned int sIndexCount;
		std::unique_ptr<Transform> mTransform;
		Transform* mParentTransform;

		Drawable();
		void UpdateTransform(bool adoptDimens = false);

	private:
		std::unique_ptr<ParentLayoutPos> mParentLayoutPos;
		std::unique_ptr<ParentLayoutCoords> mParentLayoutCoords;

		float FindHorizontalPos();
		float FindVerticalPos();
	};
}
