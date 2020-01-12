#pragma once
#include <iostream>
//creates game
#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();
int main(int argc, char** argv)
{
	std::cout << "WOOF";
	auto game = Engine::CreateApplication();  //heap memory application
	game->Run();
	delete game;
}
#endif