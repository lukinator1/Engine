#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Memorymanager.h"
#include "Messaging.h"
#include <fstream>
#undef main
#include <iostream>
std::queue <Message> messagequeue;
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Messaging Messages;
	Messages.messagingStartup();
	Window window(800, 600, "hello");
	Memorymanager memorymanager;
	memorymanager.memoryManagerstartup();
	Memorymanager::DEStackAllocator* memory = memorymanager.newAllocator(600, alignof(int));
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


/*Memorymanager test;
Memorymanager::DEStackAllocator* memory = test.newAllocator(600, alignof(int));
int* atest = (int*)memory->engineAllocate(50, 4, false);
atest[13] = -18;
atest[99] = 2;
char* testtwo = (char*)memory->engineAllocate(50, 2, true);
int* tester = (int*)memory->engineAllocate(20, 4, false);
tester[3] = 5;
std::cout << tester[3] << std::endl;
memory->engineDeallocateToMarker();
int* omoih = (int*)memory->engineAllocate(20, 4, false);
omoih[3] = 78;
memory->clearAllocator();
test.deleteAllocator(memory);
std::cout << omoih[3];*/