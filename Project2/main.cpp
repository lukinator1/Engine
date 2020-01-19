#include "Window.h"
#include "Engine.h"
#include "Input.h"
#undef main
#include <iostream>
std::queue <Message> messagequeue;
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Window window(800, 600, "hello");
	/*GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cerr << "Glew failed to initialize!" << std::endl;
	}*/
	Input Inputs;
	Inputs.inputStartup();
	while (true) {
		Inputs.getInputs();
		Inputs.handleMessage();
		window.updateWindow();
	}
	SDL_Quit();
}