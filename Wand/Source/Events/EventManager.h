#pragma once

#include "Event.h"
#include "UI/UIEntity.h"
#include "Core/Window.h"
#include "Input/Input.h"
#include "Graphics/Renderer.h"
#include "Graphics/Base/Transform.h"
#include "Core/CursorManager.h"

namespace wand
{
	class EventManager
	{
	public:
		EventManager();
		void Init(Window* window, Input* input, Renderer* renderer, CursorManager* cursorManager);
		// Clear the events of the last frame
		void Clear();
		// Save the entities for this frame
		void SetEntities(std::vector<std::unique_ptr<UIEntity>>& entities);
		// Handle window and input events
		void HandleEvent(Event* event);

	private:
		std::vector<UIEntity*> mEntities;
		std::vector<UIEntity*> mActiveEntities;
		Window* mWindow;
		Input* mInput;
		Renderer* mRenderer;
		CursorManager* mCursorManager;
		double mXPos;
		double mYPos;

		void HandleWindowEvent(Event* windowEvent);
		void HandleInputEvent(Event* inputEvent);

		void ProcessWindowResize(WindowResizeEvent* event);
		bool ProcessUIEvent(Event* event);
		// Run a function corresponding to a UI entity
		bool ProcessUIFunction(UIEntity* entity, Event* event);

		void ResetWindowBounds(WindowResizeEvent* event, glm::vec2& pos, glm::vec2& dimens);
		void ResizeEntities(glm::vec2 scale);
		// Return true if the cursor is inside the entity bounds
		bool IsMouseInArea(Transform* transform);
		// Sort entities based on their depth in the window
		void SortEntities(std::vector<UIEntity*>& entities) const;
	};
}
