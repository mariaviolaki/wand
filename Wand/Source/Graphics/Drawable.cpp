#include "WandPCH.h"
#include "Drawable.h"

namespace wand
{
	/******************** STATIC VARIABLES ***********************/
	const unsigned int Drawable::sIndexCount = 6;
	const unsigned int Drawable::sSize = 4 * sizeof(Vertex);

	/******************** STATIC FUNCTIONS ***********************/
	// Get the number of indices to render 1 rectangle (= 2 triangles)
	unsigned int Drawable::GetIndexCount() { return sIndexCount; }
	// Get the size in bytes for 1 rectangle (= 4 vertices)
	unsigned int Drawable::GetSize() { return sSize; }

	/********************** CONSTRUCTORS *************************/

	Drawable::Drawable(glm::vec4 color)
		: mColor(color), mTransform(std::make_shared<Transform>()), 
		mTexture(std::make_shared<Texture>()), mVertices(std::make_shared<std::array<Vertex, 4>>())
	{}

	Drawable::Drawable(const std::string& imagePath)
		: mColor({ 1.0f ,1.0f ,1.0f ,1.0f }), mTransform(std::make_shared<Transform>()),
		mTexture(std::make_shared<Texture>(imagePath)), mVertices(std::make_shared<std::array<Vertex, 4>>())
	{
		SetWidth(mTexture->GetWidth());
		SetHeight(mTexture->GetHeight());
	}
	/******************** TRANSFORM METHODS **********************/

	glm::vec3 Drawable::GetPosition() const	{ return mTransform->GetPosition(); }
	float Drawable::GetWidth() const { return mTransform->GetWidth(); }
	float Drawable::GetHeight() const { return mTransform->GetHeight(); }

	void Drawable::SetPosition(float x, float y) { mTransform->SetPosition(x, y); }
	void Drawable::SetWidth(float width) { mTransform->SetWidth(width); }
	void Drawable::SetHeight(float height) { mTransform->SetHeight(height); }

	/********************* DRAWABLE METHODS **********************/

	unsigned int Drawable::GetTexId() const	{ return mTexture->GetId(); }

	glm::vec4 Drawable::GetColor() const { return mColor; }

	void Drawable::SetColor(glm::vec4 color) { mColor = color; }

	void Drawable::SetTextureSlot(int slot)	{ mTexture->Bind(slot);	}

	std::array<Vertex, 4>* Drawable::GetVertexData()
	{
		// Bottom left corner
		mVertices->at(0).position =
		{
			GetPosition().x, GetPosition().y, GetPosition().z
		};
		mVertices->at(0).color = mColor;
		mVertices->at(0).texCoords = { 0.0f, 0.0f };
		mVertices->at(0).texSlot = (float) mTexture->GetTexSlot();

		// Bottom right corner
		mVertices->at(1).position =
		{
			GetPosition().x + GetWidth(), GetPosition().y, GetPosition().z
		};
		mVertices->at(1).color = mColor;
		mVertices->at(1).texCoords = { 1.0f, 0.0f };
		mVertices->at(1).texSlot = (float)mTexture->GetTexSlot();

		// Top right corner
		mVertices->at(2).position =
		{
			GetPosition().x + GetWidth(), GetPosition().y + GetHeight(), GetPosition().z
		};
		mVertices->at(2).color = mColor;
		mVertices->at(2).texCoords = { 1.0f, 1.0f };
		mVertices->at(2).texSlot = (float)mTexture->GetTexSlot();

		// Top left corner
		mVertices->at(3).position =
		{
			GetPosition().x, GetPosition().y + GetHeight(), GetPosition().z
		};
		mVertices->at(3).color = mColor;
		mVertices->at(3).texCoords = { 0.0f, 1.0f };
		mVertices->at(3).texSlot = (float)mTexture->GetTexSlot();

		return mVertices.get();
	}
}
