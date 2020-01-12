#include "Application.h"
#include <iostream>

namespace Engine {
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run() {
		while (true)
		{
			std::cout << "The game is running.";
		}
	}
}
