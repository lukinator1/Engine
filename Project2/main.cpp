#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"
#include "Memorymanager.h"
#include "Messaging.h"
#include <fstream>
#undef main
#include <iostream>
std::queue <Message> messagequeue;
double deltatime = 1.0/30.0;
double gametime = 0.0;
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
	Vertex vertices[] =
	{
		Vertex(vector3(-0.5f, -0.5f, 0.0f)),
		Vertex(vector3(0.0f, 0.5f, 0.0f)),
		Vertex(vector3(0.5f, -0.5f, 0.0f))
	};
	Mesh meshme(vertices, sizeof(vertices)/sizeof(vertices[0]), 3); 
	Shader shaderit;
	shaderit.addVertexShader(shaderit.loadShader("Shaders/Vertex.vs"));
	shaderit.addFragmentShader(shaderit.loadShader("Shaders/Fragment.fs"));
	shaderit.compileShader();

	int framerate = 0;
	double framecounter = 0;
	std::chrono::high_resolution_clock::time_point starttime;
	std::chrono::high_resolution_clock::time_point endtime;
	std::chrono::duration<double> timeduration;
	std::chrono::duration<double> chronodelta = std::chrono::duration<double>(deltatime);
	while (true) {
		starttime = std::chrono::high_resolution_clock::now();
		memorymanager.memorymanagerUpdate();
		Messages.messageUpdate(Inputs, window);
		Inputs.getInputs();
		window.clearWindow(0.2f, 0.3f, 0.3f, 0.0f);
		shaderit.useShader();
		meshme.drawMesh();

		window.swapWindow();
		framerate++;
		gametime += chronodelta.count();
		endtime = std::chrono::high_resolution_clock::now();
		timeduration = std::chrono::duration_cast<std::chrono::duration<double>> (endtime - starttime);
		if (timeduration < chronodelta)
		{
			std::this_thread::sleep_for(chronodelta - timeduration);
			framecounter += chronodelta.count();
		}
		else if (timeduration > chronodelta) {
			std::this_thread::sleep_for(chronodelta - (timeduration - chronodelta)); //todo: change to division
			framecounter += chronodelta.count() + chronodelta.count();
			std::cout << "slow" << std::endl;
		}
		if (framecounter >= 1.0) {
			std::cout << framerate << " FPS" << std::endl;
			framecounter = 0;
			framerate = 0;
		}
	}
		SDL_Quit();
}

/*int* test = (int *)memorymanager.sfAllocator.engineAllocate(200, 8, false);
char* testme = (char *)memorymanager.dbAllocator.engineAllocate(167, 8, false);*/
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
		/*if ((gametime > 59 && gametime < 61) || (gametime > 119 && gametime < 121) || (gametime > 179 && gametime < 181) || (gametime > 239 && gametime < 241) || (gametime < 299 && gametime > 301)) {
			std::cout << "current game time: " << gametime << std::endl;
		}*/
/*
glFrontFace(GL_CW);
glCullface(GL_Back);
glEnable(GL_CULL_FACE);
glEnable(GL_DEPTH_TEST);
glEnable(GL_FRAMEBUFFER_SRGB); //gamma correction
*/