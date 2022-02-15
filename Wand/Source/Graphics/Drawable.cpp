#include "WandPCH.h"
#include "Drawable.h"

namespace wand
{
	/******************** STATIC VARIABLES ***********************/
	const unsigned int Drawable::sIndexCount = 6;

	/******************** STATIC FUNCTIONS ***********************/
	// Get the number of indices to render 1 rectangle (= 2 triangles)
	unsigned int Drawable::GetIndexCount() { return sIndexCount; }

	/******************** DRAWABLE METHODS **********************/
	Drawable::Drawable(glm::vec2 dimens)
		: mTransform(std::make_shared<Transform>(dimens))
	{}

	glm::vec3 Drawable::GetPosition() const	{ return mTransform->GetPosition(); }
	float Drawable::GetWidth() const { return mTransform->GetWidth(); }
	float Drawable::GetHeight() const { return mTransform->GetHeight(); }

	void Drawable::SetPosition(float x, float y) { mTransform->SetPosition(x, y); }
	void Drawable::SetWidth(float width) { mTransform->SetWidth(width); }
	void Drawable::SetHeight(float height) { mTransform->SetHeight(height); }
}
