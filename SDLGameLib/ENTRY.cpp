#include "Src/SDLApplication.h"
#include "../Game.h"

#include <Windows.h>

int main(int, char**)
{
	game_handler = new Game();

    application = new SDLApplication(
		ApplicationSettings::window_name, 
		ApplicationSettings::VideoSettings::default_window_width, 
		ApplicationSettings::VideoSettings::default_window_height
	);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SDLApplication::Update, 0, 0, 0);
	
	if (!application->Run())
	{
		std::cout << "Error Initializing SDL Application, exiting!" << std::endl;
		return EXIT_FAILURE;
	}

	application->UpdateRender();
	application->Destroy();

	delete application;

    return EXIT_SUCCESS;
}
