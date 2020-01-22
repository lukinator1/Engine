#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Messaging.h"
#include <fstream>
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

	Logger logger;
	logger.startUp();
	Input Inputs;
	Inputs.inputStartup();
	Messaging Messages;
	Messages.messagingStartup();
	while (true) {
		Messages.messageUpdate(Inputs, window);
		Inputs.getInputs();
		window.updateWindow();

	}
	SDL_Quit();
}