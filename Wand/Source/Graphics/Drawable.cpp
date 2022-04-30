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
	void Drawable::SetTransform(bool isLayoutChild) { mTransform.reset(new Transform(isLayoutChild)); }
	const Transform* Drawable::GetParentTransform() const { return mParentTransform; }
	void Drawable::SetParentTransform(Transform* transform) { mParentTransform = transform; }

	void Drawable::SetParentLayoutPos(LayoutPosition horizontal, LayoutPosition vertical)
	{
		mParentLayoutPos = std::make_unique<ParentLayoutPos>(ParentLayoutPos({ horizontal, vertical }));
	}

	void Drawable::SetParentLayoutCoords(float x, float y)
	{
		mParentLayoutCoords = std::make_unique<ParentLayoutCoords>(ParentLayoutCoords({ x, y }));
	}

	void Drawable::UpdateTransform(bool adoptDimens)
	{
		if (!mParentTransform)
			return;

		float width, height;
		if (adoptDimens)
		{
			width = mParentTransform->GetWidth();
			height = mParentTransform->GetHeight();
		}
		else // keep own dimensions
		{
			width = mTransform->GetWidth();
			height = mTransform->GetHeight();
		}
		SetTransform(true);
		mTransform->SetDepth(mParentTransform->GetDepth());
		mTransform->SetScale(mParentTransform->GetScale().x, mParentTransform->GetScale().y);
		mTransform->SetWidth(width);
		mTransform->SetHeight(height);
		if (mParentLayoutPos)
			SetParentLayoutPos();
		else if (mParentLayoutCoords)
			mTransform->SetPos(mParentTransform->GetPos().x + mParentLayoutCoords->x,
				mParentTransform->GetPos().y + mParentLayoutCoords->y);
	}

	void Drawable::SetParentLayoutPos()
	{
		float x, y;

		// Set position on the x axis
		if (mParentLayoutPos->horizontal == LayoutPosition::LEFT)
			x = mParentTransform->GetPos().x;
		else if (mParentLayoutPos->horizontal == LayoutPosition::RIGHT)
			x = mParentTransform->GetPos().x + mParentTransform->GetWidth() - mTransform->GetWidth();
		else // align at center
			x = mParentTransform->GetPos().x + (mParentTransform->GetWidth() / 2) - (mTransform->GetWidth() / 2);

		// Set position on the y axis
		if (mParentLayoutPos->vertical == LayoutPosition::BOTTOM)
			y = mParentTransform->GetPos().y;
		else if (mParentLayoutPos->vertical == LayoutPosition::TOP)
			y = mParentTransform->GetPos().y + mParentTransform->GetHeight() - mTransform->GetHeight();
		else // align at center
			y = mParentTransform->GetPos().y + (mParentTransform->GetHeight() / 2) - (mTransform->GetHeight() / 2);

		mTransform->SetPos(x, y);
	}
}
