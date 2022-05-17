#pragma once

#include "UI/Sprite.h"

namespace wand
{
	class VNEntity
	{
	protected:
		VNEntity(std::string name);

	public:
		/******************** VN-RELATED METHODS ************************/
		// Add and manage an already loaded sprite
		void AddSprite(Sprite* sprite);
		// Only show and enable the sprite with the specified label
		void SetSprite(std::string spriteLabel);
		/* The name that all sprites have in common */
		void SetName(std::string name);
		std::string GetName() const;

		/**************** TRANSFORM-RELATED METHODS *********************/
		Transform* GetTransform();
		Vector2 GetPos() const;
		Vector2 GetScale() const;
		float GetLayer() const;
		float GetWidth() const;
		float GetHeight() const;
		float GetRotation() const;
		FlipAxis GetFlipAxis() const;
		void SetPos(float x, float y);
		void SetScale(float x, float y);
		void SetLayer(float layer);
		void SetWidth(float width);
		void SetHeight(float height);
		void SetRotation(float rotation);
		void SetFlip(FlipAxis flipAxis);

		/******************* UI-RELATED METHODS *************************/
		/* Visibility methods set if the entity should be rendered or not */
		bool IsVisible() const;
		virtual void Show();
		virtual void Hide();
		/* These methods set if the user can interact with the entity or not */
		bool IsEnabled() const;
		virtual void Enable();
		virtual void Disable();
		/* Use a label to distinguish UI entities */
		std::string GetLabel() const;
		void SetLabel(const std::string& label);
		/* Set functions that run depending on user input */
		void OnLeftClick(const std::function<void()>& fun);
		void OnRightClick(const std::function<void()>& fun);
		void OnHover(const std::function<void()>& fun);
		/* Functions for entities that are children of another entity */
		void SetParentLayout(Transform* layout);
		void SetLayoutPosition(float x, float y);
		void SetLayoutPosition(LayoutPosition horizontal, LayoutPosition vertical);

	private:
		std::vector<Sprite*> mSprites;
		Sprite* mCurrentSprite;
		std::string mName;
	};
}
