#include "Application.h"
#include <iostream>

namespace Engine {
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() { //main game loop
		while (true)
		{
			std::cout << "The game is running.";
		}
	}
}
