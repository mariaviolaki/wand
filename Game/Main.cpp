#include "Wand.h"

/*
	The 'Game' project in this solution is intended for the game developer.
	Add audio files inside the 'Game/Audio/' folder.
	Add images inside the 'Game/Images/' folder.
	Add font files inside the 'Game/Fonts/' folder.
	Saved states should be inside the 'Game/Saves/' folder.
	A 'log.txt' file is created upon startup in the solution folder and can be used for debugging.
*/

// Entry point for windows applications
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// Create a new app
	std::shared_ptr<wand::App> app = std::make_shared<wand::App>();

	/* Code that runs before the game starts goes here */

	while (app->IsRunning())
	{
		app->Clear();

		/* Code that runs each frame goes here */

		app->Update();
	}
	return 0;
}
