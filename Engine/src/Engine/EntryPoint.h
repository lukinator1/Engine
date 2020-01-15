#pragma once
#include <iostream>
#include "Message.h"
#include "GL/glew.h"
#ifdef ENGINE_PLATFORM_WINDOWS
std::queue<Message> messageque;
extern Engine::Application* Engine::CreateApplication();
int main(int argc, char** argv)
{
	std::cout << "WOOF";
	auto game = Engine::CreateApplication();  //heap memory application
	game->Run();
	delete game;
}
#endif