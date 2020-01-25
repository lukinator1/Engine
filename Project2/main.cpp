#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Memorymanager.h"
#include "Messaging.h"
#include <fstream>
#undef main
#include <iostream>
//funkey
std::queue <Message> messagequeue;
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Messaging Messages;
	Messages.messagingStartup();
	Window window(800, 600, "hello");
	Memorymanager memorymanager;
	memorymanager.memoryManagerstartup();
	Memorymanager::StackAllocator* stackallocator = memorymanager.newAllocator(500, alignof(int));
	Input Inputs;
	Inputs.inputStartup();
	int counter = 0;
	char *temp = nullptr;


	while (true) {
		memorymanager.memorymanagerUpdate();
		Messages.messageUpdate(Inputs, window);
		Inputs.getInputs();
		window.updateWindow();
		int* test = (int *)memorymanager.sfAllocator.engineAllocate(200, 8, false);
		char* testme = (char *)memorymanager.dbAllocator.engineAllocate(167, 8, false);
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
/*if (counter < 5) {
	test[0] = 143;
	std::cout << test[0] << std::endl;
	testme[7] = '2';
	std::cout << testme[7] << std::endl;
}
else {
	test[0] = 1212;
	std::cout << test[0] << std::endl;
	testme[7] = 'p';
	std::cout << testme[7] << std::endl;
}*/
/*if (counter % 2 == 0) {
			testme[7] = '2';
			temp = &testme[7];
		}
		else {
			testme[7] = 'p';
		}
		if (counter > 4) {
		std::cout << *temp << std::endl;
	}
		std::cout << testme[7] << std::endl;
		counter++;*/