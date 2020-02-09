#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"
#include "Materials.h"
#include "Texture.h"
#include "Directionallight.h"
#include "Transforming.h"
#include "Memorymanager.h"
#include "Messaging.h"
#include <fstream>
#undef main
#include <iostream>
std::queue <Message> messagequeue;
float deltatime = 1.0f/60.0f;
float gametime = 0.0f;
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
	glEnable(GL_TEXTURE_2D);
	Camera thecamera;
	Transforming transform;
	Vertex vertices[] =
	{					//position, texture
		Vertex(vector3(-1.0f, -1.0f, 0.0f), vector2(0.0f,0.0f)),
		Vertex(vector3(0.0f, 1.0, 0.0f), vector2(0.5f , 0.0f)),
		Vertex(vector3(1.0f, -1.0f, 0.0f), vector2(1.0f, 0.0f)),
		Vertex(vector3(0.0f, -1.0f, 1.0f), vector2(0.0f, 0.5f))
	};
	unsigned int indices[] = {
		3, 1, 0,
		2, 1, 3,
		0, 1, 2,
		0, 2, 3
	};
	Mesh meshme(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
	/*Mesh meshme;
	meshme.loadMeshObj("Models/quote.obj");*/
	Shader shaderit;
	/*Texture text;
	text.loadTexture("Textures/test.png");*/
	shaderit.addVertexShader(shaderit.loadShader("Shaders/Phongvertexshader.vs"));
	shaderit.addFragmentShader(shaderit.loadShader("Shaders/Phongfragmentshader.fs"));
	shaderit.compileShader();
	shaderit.addUniform("color");
	shaderit.addUniform("transform");
	shaderit.addUniform("projectedtransform");
	shaderit.addUniform("uniformFloat");
	shaderit.addUniform("ambientlight");
	shaderit.addUniform("directionallight.color");
	shaderit.addUniform("directionallight.intensity");
	shaderit.addUniform("directionallight.direction");
	shaderit.setAmbientLight(vector3(0.1f, 0.1f, 0.1f));
	shaderit.setDirectionalLight(Directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 1.0f));

	Materials material("Textures/test.png", vector3(0.0f, 1.0f, 1.0f));		// from basicshader change to render manager startup?

	float previousscrolldistance;
	float unitest = 0.0f;
	int framerate = 0;
	double framecounter = 0;
	std::chrono::high_resolution_clock::time_point starttime;
	std::chrono::high_resolution_clock::time_point endtime;
	std::chrono::duration<double> timeduration;
	std::chrono::duration<double> chronodelta = std::chrono::duration<double>(deltatime);
	thecamera.setMouseLook(true);
	while (true) {
		starttime = std::chrono::high_resolution_clock::now();
		memorymanager.memorymanagerUpdate();
		Messages.messageUpdate(Inputs, window, thecamera);
		Inputs.getInputs();
		window.updateWindow();
		if (Inputs.keyboardstate[Input::W] == 1) {
			thecamera.moveCamera(thecamera.getForwardvector(), .3f);
		}
		if (Inputs.keyboardstate[Input::A] == 1) {
			thecamera.moveCamera(thecamera.getLeftVector(), .3f);
		}
		if (Inputs.keyboardstate[Input::S] == 1) {
			thecamera.moveCamera(thecamera.getForwardvector(), -.3f);
		}
		if (Inputs.keyboardstate[Input::D] == 1) {
			thecamera.moveCamera(thecamera.getLeftVector(), -.3f);
		}
		if (Inputs.keyboardstate[Input::keyup] == 1) {
			thecamera.rotateCamera(0.0f,2.0f);
		}
		if (Inputs.keyboardstate[Input::keyleft] == 1) {
			thecamera.rotateCamera(-2.0f, 0.0f);
		}
		if (Inputs.keyboardstate[Input::keydown] == 1) {
			thecamera.rotateCamera(0.0f, -2.0f);
		}
		if (Inputs.keyboardstate[Input::keyright] == 1) {
			thecamera.rotateCamera(2.0f, 0.0f);
		}
		if (Inputs.getScrolldistance().y != 0) {
			thecamera.Zoom(Inputs.getScrolldistance().y);
		}
		if (Inputs.getMouseMovementDistance().x != 0 || Inputs.getMouseMovementDistance().y != 0) {
			thecamera.rotateCamera(Inputs.getXMouseMovementDistance(), Inputs.getYMouseMovementDistance());
		}


		shaderit.setUniform("uniformFloat", (float)sin(unitest)); 
		transform.setTranslationVector(vector3(sin(unitest), 0, 5));
		transform.setRotationVector(vector3(0, sin(unitest) * 180, 0));
		transform.setPerspectiveProjectionSettings(thecamera.fov, window.getWindowWidth(), window.getWindowHeight(), thecamera.minviewdistance, thecamera.maxviewdistance);  //integer -> float
		/*transform.setScalingVector(vector3(.75 * sin(unitest), .75 * sin(unitest), .75 * sin(unitest)));*/
		/*transform.orthographicprojection = false;*/
		shaderit.useShader();
		/*shaderit.setUniform("transform", transform.newTransformationMatrix());
		shaderit.setUniform("color", vector3(0.0f, 1.0f, 1.0f));
		text.bindTexture();*/
		shaderit.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), material);
		meshme.drawMesh();



		unitest += deltatime;
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