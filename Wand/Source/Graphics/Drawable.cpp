#include "WandPCH.h"
#include "Drawable.h"
#include "Renderer.h"

namespace wand
{
	/******************** STATIC VARIABLES ***********************/
	const unsigned int Drawable::sIndexCount = 6;

	/******************** STATIC FUNCTIONS ***********************/
	// Get the number of indices to render 1 rectangle (= 2 triangles)
	unsigned int Drawable::GetIndexCount() { return sIndexCount; }

	/******************** DRAWABLE METHODS **********************/
	Drawable::Drawable()
		: mTransform(std::make_unique<Transform>()), mParentTransform(nullptr)
	{}

	Transform* Drawable::GetTransform() const { return mTransform.get(); }
	const Transform* Drawable::GetParentTransform() const { return mParentTransform; }
	void Drawable::SetParentTransform(Transform* transform) { mParentTransform = transform; }

	void Drawable::SetParentLayoutPos(LayoutPosition horizontal, LayoutPosition vertical)
	{
		mTransform->SetLayoutChild(true);
		mParentLayoutPos = std::make_unique<ParentLayoutPos>(ParentLayoutPos({ horizontal, vertical }));
	}

	void Drawable::SetParentLayoutCoords(float x, float y)
	{
		mTransform->SetLayoutChild(true);
		mParentLayoutCoords = std::make_unique<ParentLayoutCoords>(ParentLayoutCoords({ x, y }));
	}

	void Drawable::UpdateTransform()
	{
		if (!mParentTransform)
			return;

		mTransform->SetLayoutChild(true);
		mTransform->SetLayer(mParentTransform->GetLayer());
		mTransform->SetScale(mParentTransform->GetScale().x, mParentTransform->GetScale().y);
		if (mParentLayoutPos)
			mTransform->SetPos(FindHorizontalPos(), FindVerticalPos());
		else if (mParentLayoutCoords)
			mTransform->SetPos(mParentTransform->GetPos().x + mParentLayoutCoords->x,
				mParentTransform->GetPos().y + mParentLayoutCoords->y);
	}

	float Drawable::FindHorizontalPos()
	{
		float x;
		// Set position on the x axis
		if (mParentLayoutPos->horizontal == LayoutPosition::LEFT)
		{
			x = mParentTransform->GetPos().x;
		}
		else if (mParentLayoutPos->horizontal == LayoutPosition::RIGHT)
		{
			x = mParentTransform->GetPos().x + mParentTransform->GetWidth() - mTransform->GetWidth();
		}
		else // align at center
		{
			float parentMiddle = mParentTransform->GetPos().x + (mParentTransform->GetWidth() / 2);
			if (mParentLayoutPos->horizontal == LayoutPosition::MIDLEFT)
				x = (parentMiddle - mParentTransform->GetPos().x) / 2 + mParentTransform->GetPos().x;
			else if (mParentLayoutPos->horizontal == LayoutPosition::MIDRIGHT)
				x = (mParentTransform->GetPos().x + mParentTransform->GetWidth() - parentMiddle) / 2 + parentMiddle;
			else // align at center
				x = parentMiddle;
			x -= mTransform->GetWidth() / 2;
		}
		return x;
	}

	float Drawable::FindVerticalPos()
	{
		float y;
		// Set position on the y axis
		if (mParentLayoutPos->vertical == LayoutPosition::BOTTOM)
		{
			y = mParentTransform->GetPos().y;
		}
		else if (mParentLayoutPos->vertical == LayoutPosition::TOP)
		{
			y = mParentTransform->GetPos().y + mParentTransform->GetHeight() - mTransform->GetHeight();
		}
		else // align at center
		{
			float parentMiddle = mParentTransform->GetPos().y + (mParentTransform->GetHeight() / 2);
			if (mParentLayoutPos->vertical == LayoutPosition::MIDBOTTOM)
				y = (parentMiddle - mParentTransform->GetPos().y) / 2 + mParentTransform->GetPos().y;
			else if (mParentLayoutPos->vertical == LayoutPosition::MIDTOP)
				y = (mParentTransform->GetPos().y + mParentTransform->GetHeight() - parentMiddle) / 2 + parentMiddle;
			else
				y = parentMiddle;
			y -= mTransform->GetHeight() / 2;
		}
		return y;
	}
}
