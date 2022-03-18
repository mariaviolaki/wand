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
		: mTransform(std::make_shared<Transform>())
	{}
	
	std::shared_ptr<Transform> Drawable::GetTransform() const { return mTransform; }
}
