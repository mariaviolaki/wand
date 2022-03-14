#include "WandPCH.h"
#include "UIManager.h"
#include "Input/Input.h"

namespace wand
{
	std::vector<UIComponent*> UIManager::components;

	void UIManager::Add(UIComponent* component)
	{
		components.push_back(component);
	}

	void UIManager::ProcessClickFunction()
	{
		if (components.empty())
			return;

		// Sort components based on their depth by providing a comparison function
		std::sort(components.begin(), components.end(),
			[](const UIComponent* a, const UIComponent* b)
			{
				// Sort in descending order
				return a->GetUITransform().GetDepth() > b->GetUITransform().GetDepth();
			});

		// Run the function of the component in front of the others
		components[0]->GetFunction()();
		Input::ProcessClick(MOUSE_BUTTON_LEFT);
		// Clear the vector for the current frame
		components.clear();
	}
}
