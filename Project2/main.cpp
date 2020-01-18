#include "Window.h"
#include "Engine.h"
#undef main
#include <iostream>
std::queue <Message> messagequeue;
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Window window(800, 600, "hello");
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}
	while (true) {
		window.updateWindow();
	}
	SDL_Quit();
}