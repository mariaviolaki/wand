#include "WandPCH.h"
#include "Layout.h"

namespace wand
{
	Layout::Layout()
		: mTransform(std::make_shared<Transform>())
	{}

	glm::vec3 Layout::GetPosition() const { return mTransform->GetPosition(); }
	float Layout::GetWidth() const { return mTransform->GetWidth(); }
	float Layout::GetHeight() const { return mTransform->GetHeight(); }

	void Layout::SetPosition(float x, float y) { mTransform->SetPosition(x, y); }
	void Layout::SetWidth(float width) { mTransform->SetWidth(width); }
	void Layout::SetHeight(float height) { mTransform->SetHeight(height); }
}