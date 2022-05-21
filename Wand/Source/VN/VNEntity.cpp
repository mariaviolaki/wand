#include "WandPCH.h"
#include "VNEntity.h"

namespace wand
{
	VNEntity::VNEntity(std::string name)
		: mSprites(), mCurrentSprite(nullptr), mName(name)
	{}

	void VNEntity::AddSprite(Sprite* sprite)
	{
		mSprites.emplace_back(sprite);
		mCurrentSprite = sprite;
	}

	void VNEntity::SetSprite(std::string spriteLabel)
	{
		for (auto& sprite : mSprites)
		{
			// If the sprite has the same label as the target, set it as visible
			if (sprite->GetLabel() == spriteLabel)
			{
				sprite->Show();
				mCurrentSprite = sprite;
			}
			else // hide all the other sprites
			{
				sprite->Hide();
			}
		}
	}

	void VNEntity::SetName(std::string name) { mName = name; }
	std::string VNEntity::GetName() const { return mName; }

	Transform* VNEntity::GetTransform() { return mCurrentSprite->GetTransform(); }
	Vector2 VNEntity::GetPos() const { return mCurrentSprite->GetTransform()->GetPos(); }
	Vector2 VNEntity::GetScale() const { return mCurrentSprite->GetTransform()->GetScale(); }
	float VNEntity::GetLayer() const { return mCurrentSprite->GetTransform()->GetLayer(); }
	float VNEntity::GetWidth() const { return mCurrentSprite->GetTransform()->GetWidth(); }
	float VNEntity::GetHeight() const { return mCurrentSprite->GetTransform()->GetHeight(); }
	float VNEntity::GetRotation() const { return mCurrentSprite->GetTransform()->GetRotation(); }
	FlipAxis VNEntity::GetFlipAxis() const { return mCurrentSprite->GetTransform()->GetFlip(); }

	void VNEntity::SetPos(float x, float y)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetPos(x, y);
	}
	void VNEntity::SetScale(float x, float y)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetScale(x, y);
	}
	void VNEntity::SetLayer(float layer)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetLayer(layer);
	}
	void VNEntity::SetWidth(float width)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetWidth(width);
	}
	void VNEntity::SetHeight(float height)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetHeight(height);
	}
	void VNEntity::SetRotation(float rotation)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetRotation(rotation);
	}
	void VNEntity::SetFlip(FlipAxis flipAxis)
	{
		for (auto& sprite : mSprites)
			sprite->GetTransform()->SetFlip(flipAxis);
	}

	bool VNEntity::IsVisible() const { return mCurrentSprite->IsVisible(); }
	void VNEntity::Show() { mCurrentSprite->Show(); }
	void VNEntity::Hide()
	{
		for (auto& sprite : mSprites)
			sprite->Hide();
	}
	bool VNEntity::IsEnabled() const { return mCurrentSprite->IsEnabled(); }
	void VNEntity::Enable()
	{
		for (auto& sprite : mSprites)
			sprite->Enable();
	}
	void VNEntity::Disable()
	{
		for (auto& sprite : mSprites)
			sprite->Disable();
	}
	std::string VNEntity::GetLabel() const { return mCurrentSprite->GetLabel(); }
	void VNEntity::SetLabel(const std::string& label) { mCurrentSprite->SetLabel(label); }
	void VNEntity::OnLeftClick(const std::function<void()>& fun)
	{
		for (auto& sprite : mSprites)
			sprite->OnLeftClick(fun);
	}
	void VNEntity::OnRightClick(const std::function<void()>& fun)
	{
		for (auto& sprite : mSprites)
			sprite->OnRightClick(fun);
	}
	void VNEntity::OnHover(const std::function<void()>& fun)
	{
		for (auto& sprite : mSprites)
			sprite->OnHover(fun);
	}
	void VNEntity::SetParentLayout(Transform* layout)
	{
		for (auto& sprite : mSprites)
			sprite->SetParentLayout(layout);
	}
	void VNEntity::SetLayoutPosition(float x, float y)
	{
		for (auto& sprite : mSprites)
			sprite->SetLayoutPosition(x, y);
	}
	void VNEntity::SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical)
	{
		for (auto& sprite : mSprites)
			sprite->SetLayoutPosition(horizontal, vertical);
	}
}
