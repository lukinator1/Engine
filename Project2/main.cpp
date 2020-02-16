#include <fstream>
#include "Engine.h"
#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Rendering/Rendering.h"
#include "Mathlibrary/Mathlibrary.h"
#include "CustomMemoryAllocation/Memorymanager.h"
#include "Messaging/Messaging.h"
#include "Meshrenderer.h"
#include "Scene.h"
#include "Logger.h"
#include "Global.h"
#undef main
#include <iostream>
std::queue <Message> messagequeue;
float deltatime = 1.0f / 60.0f;
float gametime = 0.0f;
float fieldDepth = 10.0f;
float fieldWidth = 10.0f;
int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Messagesystem Messages;
	Messages.messageSystemStartup();
	Scene currentscene;
	Window window(800, 600, "hello");
	Rendering Renderer;
	Renderer.renderingStartup();
	Memorymanager memorymanager;
	memorymanager.memoryManagerstartup();
	Memorymanager::StackAllocator* stackallocator = memorymanager.newAllocator(1000, alignof(int));
	Input Inputs;
	Inputs.inputStartup();
	glEnable(GL_TEXTURE_2D);

	Skybox skybox("right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg");
	Camera thecamera;
	Transforming transform;
	Materials material("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);		// from basicshader change to render manager startup?
	Entity root;
	Mesh quote;
	quote.loadMeshObj("quote.obj");
	Meshrenderer component(quote, material);
	Meshrenderer* componentobject = &component;
	root.addComponent(componentobject);
	currentscene.root = root;

	Vertex vertices[] = { Vertex(vector3(-fieldWidth, 0.0f, -fieldDepth), vector2(0.0f, 0.0f)),
						Vertex(vector3(-fieldWidth, 0.0f, fieldDepth * 3), vector2(0.0f, 1.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, -fieldDepth), vector2(1.0f, 0.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, fieldDepth * 3), vector2(1.0f, 1.0f)) };
	unsigned int indices[] = { 0, 1, 2,
					  2, 1, 3 };
	Mesh meshme(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
	
	/*Spotlight flashlight(vector3(0.9f, 0.9f, 0.9f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 3.5f, 0.0f, 0.1f);*/
	Spotlight flashlight(vector3(0.0f, 1.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);

	Shader shaderit;

	shaderit.setAmbientLight(vector3(0.1f, 0.1f, 0.1f));
	shaderit.directionallight = Directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.1f);
	Pointlight *plights = new Pointlight[6];
	plights[0] = Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f);
	plights[1] = Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 0.8f, 0.0f, 1.0f);
	shaderit.getPointLights()[0] = &plights[0];
	shaderit.getPointLights()[1] = &plights[1];
	Spotlight *slights = new Spotlight[1];

	slights[0] = Spotlight(vector3(0.0f, 1.0f, 1.0f), vector3(-2.0f, 0.0f, 5.0f), vector3(1.0f, 1.0f, 1.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	shaderit.getSpotLights()[0] = &slights[0];

	float previousscrolldistance;
	float unitest = 0.0f;
	int framerate = 0;
	double framecounter = 0;
	std::chrono::high_resolution_clock::time_point starttime;
	std::chrono::high_resolution_clock::time_point endtime;
	std::chrono::duration<double> timeduration;
	std::chrono::duration<double> chronodelta = std::chrono::duration<double>(deltatime);
	thecamera.setMouseLook(true);
	int counter = 0;
	bool flashlighton = false;
	bool lastpressed = false;
	bool pressed = false;




	while (true) {
		starttime = std::chrono::high_resolution_clock::now();
		memorymanager.memorymanagerUpdate();
		Messages.messageSystemUpdate(Inputs, window, thecamera);
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
			thecamera.rotateCamera(0.0f, 2.0f);
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
		if (Inputs.keyboardstate[Input::L] == 1) {  //flashlight 
			if (lastpressed == false) {
				if (flashlighton == true) {
					flashlight.setIntensity(0.0f);
					flashlighton = false;
				}
				else if (flashlighton == false) {
					flashlight.setIntensity(3.0f);
					flashlighton = true;
				}
				lastpressed = true;
			}
		}
		else {
			lastpressed = false;
		}
		if (Inputs.getScrolldistance().y != 0) {
			thecamera.Zoom(Inputs.getScrolldistance().y);
		}
		if (Inputs.getMouseMovementDistance().x != 0 || Inputs.getMouseMovementDistance().y != 0) {
			thecamera.rotateCamera(Inputs.getXMouseMovementDistance(), Inputs.getYMouseMovementDistance());
		}


		transform.setTranslationVector(vector3(0.0f, -1.0f, 5.0f));
		plights[0].setPosition(vector3(3.0f, 0.0f, 8.0 * (float)(sin(unitest) + 1.0f / 2.0f) + 10.0f));
		plights[1].setPosition(vector3(7.0f, 0.0f, 8.0 * (float)(cos(unitest) + 1.0f / 2.0f) + 10.0f));
		slights[0].setPosition(thecamera.getCameraposition());
		slights[0].setDirection(thecamera.forwardvector);
		transform.setPerspectiveProjectionSettings(thecamera.fov, window.getWindowWidth(), window.getWindowHeight(), thecamera.minviewdistance, thecamera.maxviewdistance);  //integer -> float
		/*transform.setScalingVector(vector3(.75 * sin(unitest), .75 * sin(unitest), .75 * sin(unitest)));	
		shaderit.setUniform("transform", transform.newTransformationMatrix());*/
		shaderit.useShader();
		shaderit.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, material);
		meshme.drawMesh();
		Renderer.renderEntity(currentscene.root);
		skybox.useSkybox();








		unitest += deltatime;
		framerate++;
		/*gametime += chronodelta.count();*/
		endtime = std::chrono::high_resolution_clock::now();
		timeduration = std::chrono::duration_cast<std::chrono::duration<double>> (endtime - starttime);
		/*
			if (timeduration < chronodelta) //framerate lock function
			{
				std::this_thread::sleep_for(chronodelta - timeduration);
				framecounter += chronodelta.count();
			}
			else if (timeduration > chronodelta) {
				std::this_thread::sleep_for(chronodelta - (timeduration - chronodelta)); //todo: change to division
				framecounter += chronodelta.count() + chronodelta.count();
				std::cout << "slow" << std::endl;
			}
			*/
		if (framecounter >= 1.0) {
			std::cout << framerate << " FPS" << std::endl;
			framecounter = 0;
			framerate = 0;
		}
	}
	Renderer.renderingShutdown();
	SDL_Quit();
}








	/*Vertex vertices[] = half pyramid
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
	};*/
	/*Vertex vertices[] =
	{Vertex(vector3(-1.0f, -1.0f, 0.5773f), vector2(0.0f, 0.0f)),
	Vertex(vector3(0.0f, -1.0f, -1.15475f), vector2(0.5f, 0.0f)),
	Vertex(vector3(1.0f, -1.0f, 0.5773f), vector2(1.0f, 0.0f)),
	Vertex(vector3(0.0f, 1.0f, 0.0f), vector2(0.5f, 1.0f))};
	unsigned int indices[] = { 0, 3, 1,
	1, 3, 2,
	2, 3, 0,
	1, 2, 0 };*/
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