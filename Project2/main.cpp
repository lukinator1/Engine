#include <fstream>
#include <sstream>
#include "Engine.h"
#include "Thegame.h"
#include "Window.h"
#include "Input.h"
#include "Rendering/Rendering.h"
#include "Mathlibrary/Mathlibrary.h"
#include "CustomMemoryAllocation/Memorymanager.h"
#include "Messaging/Messagesystem.h"
#include "Messaging/Messaging.h"
#include "Meshrenderer.h"
#include "Scene.h"
#include "Logger.h"
#include "Global.h"
#include "Console.h"
#undef main
#include <iostream>
std::queue <Message> messagequeue;
int messagequeuecapacity = 32;
float deltatime = 1.0f / 60.0f;
float gametime = 0.0f;
bool gameisrunning = true;

float fieldDepth = 10.0f;
float fieldWidth = 10.0f;

void endGame() {
	gameisrunning = false;
}
int main(int argc, char* argv[]) {
	int count = 0;
		int sfsize = 500;  //settting configurations
		int sfalignment = 8;
		int dbsize = 500;
		int dbalignment = 8;
		bool framelock = false;
		bool vsync = false;
		std::string title = "Untitled";
		std::string windowicon = "GameWindowIcon.png";
		bool fullscreen = false;
		int windowwidth = 800;
		int windowheight = 600;
		bool desktopfullscreen = false;
		float arwidth = 800.0f;
		float arheight = 600.0f;
		bool borderless = false;
		float fov = 70.0f;
		float maxviewdistance = 1000.0f;
		float minviewdistance = 0.1f;
		unsigned int loggerchannels[4];
		unsigned int loggerverbosity = 3;
		bool loggerwarn = true;
		bool logclear = false;
		std::fstream configuration("Engineconfiguration.txt");
		std::string settings;
		while (getline(configuration, settings)) {
			if (settings.find("General:") != std::string::npos) {
				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("Unlocked") != std::string::npos || settings.find("unlocked") != std::string::npos) {
					framelock = false;
				}
				else {
					framelock = true;
					deltatime = 1.0f / stoi(settings);
				}
			}
			else if (settings.find("Window:") != std::string::npos) {
				getline(configuration, settings, '=');
				getline(configuration, settings, ' ');
				getline(configuration, settings);
				title = settings;

				getline(configuration, settings, '=');
				getline(configuration, settings, ' ');
				getline(configuration, settings);
				windowicon = settings;
				/*desktopicon = icon;*/

				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("On") != std::string::npos || settings.find("on") != std::string::npos) {
					fullscreen = true;
				}
				else {
					fullscreen = false;
				}

				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("On") != std::string::npos || settings.find("on") != std::string::npos) {
					desktopfullscreen = true;
				}
				else {
					desktopfullscreen = false;
				}

				getline(configuration, settings, '=');
				getline(configuration, settings);
				windowwidth = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				windowheight = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				arwidth = stof(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				arheight = stof(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("On") != std::string::npos || settings.find("on") != std::string::npos) {
					borderless = true;
				}
				else {
					borderless = false;
				}

				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("On") != std::string::npos || settings.find("on") != std::string::npos) {
					vsync = true;
				}
				else {
					vsync = false;
				}

			}
			else if (settings.find("Camera:") != std::string::npos) {
				getline(configuration, settings, '=');
				getline(configuration, settings);
				fov = stof(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				maxviewdistance = stof(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				minviewdistance = stof(settings);
			}
			else if (settings.find("Logger") != std::string::npos) {
				getline(configuration, settings, '=');
				getline(configuration, settings);
				std::stringstream channels(settings);
				getline(channels, settings, ',');
				Logger::enginechannels[0] = stoi(settings);
				getline(channels, settings, ',');
				Logger::enginechannels[1] = stoi(settings);
				getline(channels, settings, ',');
				Logger::enginechannels[2] = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				Logger::engineverbosity = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("On") != std::string::npos || settings.find("on") != std::string::npos || settings.find("Yes") != std::string::npos || settings.find("yes") != std::string::npos || settings.find("True") != std::string::npos || settings.find("true") != std::string::npos) {
					Logger::showwarnings = true;
				}
				else {
					Logger::showwarnings = false;
				}

				getline(configuration, settings, '=');
				getline(configuration, settings);
				if (settings.find("On") != std::string::npos || settings.find("on") != std::string::npos || settings.find("Yes") != std::string::npos || settings.find("yes") != std::string::npos || settings.find("True") != std::string::npos || settings.find("true") != std::string::npos) {
					Logger::clear = true;
				}
				else {
					Logger::clear = false;
				}
			}
			else if (settings.find("Memory:") != std::string::npos) {
				getline(configuration, settings, '=');
				getline(configuration, settings);
				sfsize = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				sfalignment = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				dbsize = stoi(settings);

				getline(configuration, settings, '=');
				getline(configuration, settings);
				dbalignment = stoi(settings);
			}
			else if (settings.find("Messaging System:") != std::string::npos) {
				getline(configuration, settings, '=');
				getline(configuration, settings);
				messagequeuecapacity = stoi(settings);
			}
		}
		configuration.close();
	/*std::ofstream start;
		if (Logger::clear) {
			start.open("Enginelogs/EngineLog.txt", std::ofstream::out);
		}
		else 
		{
			start.open("Enginelogs/EngineLog.txt", std::ofstream::out || std::ofstream::app);
		}
		if (start.is_open()) {
			start << "Current date + time: " << __TIMESTAMP__ << std::endl;
		}
		start.close();*/

	Logger log;				//startup
	log.startUp();
	Memorymanager MemoryManager(sfsize, sfalignment, dbsize, dbalignment);
	Messagesystem Messages;
	Window Window(windowwidth, windowheight, title, windowicon, fullscreen, desktopfullscreen, borderless, vsync);
	Rendering Renderer;
	Renderer.renderingStartup(Window);
	Console Console;
	Console.consoleStartup(&Renderer);
	Camera Camera;
	Camera.cameraStartup(fov, maxviewdistance, minviewdistance, arwidth, arheight);
	Transforming transform;
	Input Inputs;
	Inputs.inputStartup();






	Scene sceneone;			//test scenes
	sceneone.setSkybox("right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg");


	Entity Quote;   //quote
	Materials material("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);		// from basicshader change to render manager startup?
	Mesh quotemodel("quote.obj");
	quotemodel.loadMeshObj("quote.obj");
	Meshrenderer component(quotemodel, material);
	Meshrenderer* componentobject = &component;
	Quote.addComponent(componentobject);
	sceneone.root = Quote;

	//field
	Vertex vertices[] = { Vertex(vector3(-fieldWidth, 0.0f, -fieldDepth), vector2(0.0f, 0.0f)),
						Vertex(vector3(-fieldWidth, 0.0f, fieldDepth * 3), vector2(0.0f, 1.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, -fieldDepth), vector2(1.0f, 0.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, fieldDepth * 3), vector2(1.0f, 1.0f)) };
	unsigned int indices[] = { 0, 1, 2,
					  2, 1, 3 };
	Mesh meshme(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
	
	//shaders
	Shader shaderit;
	shaderit.setAmbientLight(vector3(0.5f, 0.5f, 0.5f));
	shaderit.directionallight = Directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.1f);

	//lights
	Spotlight flashlight(vector3(0.0f, 1.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	Pointlight *plights = new Pointlight[6];
	plights[0] = Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f);
	plights[1] = Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 0.8f, 0.0f, 1.0f);
	shaderit.getPointLights()[0] = &plights[0];
	shaderit.getPointLights()[1] = &plights[1];
	Spotlight *slights = new Spotlight[1];
	slights[0] = Spotlight(vector3(0.6f, 0.0f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), vector3(1.0f, 1.0f, 1.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	shaderit.getSpotLights()[0] = &flashlight;

	//time calculation
	int prevtimecounter = 0;
	float prevdeltatimes[5] = { 1.0f / 60.0f,  1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f };
	std::chrono::high_resolution_clock::time_point starttime;
	std::chrono::high_resolution_clock::time_point endtime;
	std::chrono::duration<float> timeduration;
	std::chrono::duration<float> chronodelta = std::chrono::duration<float>(deltatime);
	
	//engine tools
	Scene currentscene;
	int frames = 0;
	double framecounter = 0;
	int fps = -1;

	//game variable tests
	Camera.setMouseLook(false);
	bool flashlighton = true;
	float unitest = 0.0f;

	//loop
	while (gameisrunning) {
		starttime = std::chrono::high_resolution_clock::now();     //updates
		MemoryManager.memorymanagerUpdate();
		Inputs.getInputs();
		Window.updateWindow();
		Messages.messageSystemUpdate(Inputs, Window, Camera);


		//game
		if (Inputs.keyboardstate[Input::W].first == 1) {
			Camera.moveCamera(Camera.getForwardvector(), deltatime * 20);
		}
		if (Inputs.keyboardstate[Input::A].first == 1) {
			Camera.moveCamera(Camera.getLeftVector(), deltatime * 20);
		}
		if (Inputs.keyboardstate[Input::S].first == 1) {
			Camera.moveCamera(Camera.getForwardvector(), -(deltatime * 20));
		}
		if (Inputs.keyboardstate[Input::D].first == 1) {
			Camera.moveCamera(Camera.getLeftVector(), -(deltatime * 20));
		}
		if (Inputs.keyboardstate[Input::Keyup].first == 1) {
			Camera.rotateCamera(0.0f, 2.0f);
		}
		if (Inputs.keyboardstate[Input::Keyleft].first == 1) {
			Camera.rotateCamera(-2.0f, 0.0f);
		}
		if (Inputs.keyboardstate[Input::Keydown].first == 1) {
			Camera.rotateCamera(0.0f, -2.0f);
		}
		if (Inputs.keyboardstate[Input::Keyright].first == 1) {
			Camera.rotateCamera(2.0f, 0.0f);
		}
		if (Inputs.keyboardstate[Input::L].first == 1 && Inputs.keyboardstate[Input::L].second == 0) {  //flashlight 
				if (flashlighton == true) {
					flashlight.setIntensity(0.0f);
					flashlighton = false;
				}
				else if (flashlighton == false) {
					flashlight.setIntensity(3.0f);
					flashlighton = true;
				}
		}
		if (Inputs.getScrolldistance().y != 0) {
			Camera.Zoom(Inputs.getScrolldistance().y);
		}
		if (Inputs.getMouseMovementDistance().x != 0 || Inputs.getMouseMovementDistance().y != 0) {
			Camera.rotateCamera(Inputs.getXMouseMovementDistance(), Inputs.getYMouseMovementDistance());
		}
		if (Window.closeRequested() == true) {
			endGame();
		}

		//enginetests
		transform.setTranslationVector(vector3(0.0f, -1.0f, 5.0f));
		plights[0].setPosition(vector3(3.0f, 0.0f, 8.0 * (float)(sin(unitest) + 1.0f / 2.0f) + 10.0f));
		plights[1].setPosition(vector3(7.0f, 0.0f, 8.0 * (float)(cos(unitest) + 1.0f / 2.0f) + 10.0f));
		unitest += deltatime;
		flashlight.setPosition(Camera.getCameraposition());
		flashlight.setDirection(Camera.forwardvector);
		shaderit.useShader();
		shaderit.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, material);
		meshme.drawMesh();
		Renderer.renderScene(sceneone);
		Renderer.Textrenderer.renderText("texter", 510.0f,  300.0f, vector3(1.0f, 1.0f, 1.0f), .4f);
		Renderer.Textrenderer.renderText("The quick brown fox jumped over the lazy dog. 1234567890", 0.0f, 300.0f, vector3(0.4, 0.3, 0.8), .7f);


		







		//time calculations
		frames++;
		endtime = std::chrono::high_resolution_clock::now();
		timeduration = (endtime - starttime);
		if (framelock == false) {
			prevdeltatimes[prevtimecounter] = timeduration.count();
			prevtimecounter++;
			if (prevtimecounter == 5) {
				prevtimecounter = 0;
			}
			deltatime = (prevdeltatimes[0] + prevdeltatimes[1] + prevdeltatimes[2] + prevdeltatimes[3] + prevdeltatimes[4]) / 5.0f;
			framecounter += deltatime;
		}
		else if (framelock == true) {
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
			}
		if (framecounter >= 1.0) {
			fps = frames;
			framecounter = 0;
			frames = 0;
		}
		Renderer.Textrenderer.renderText(std::to_string(deltatime), 0, 200, vector3(1.0, 1.0, 1.0), 1.0);
		Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, 500, vector3(1.0, 1.0, 1.0), 1.0);
	}

	//Shutdown
	MemoryManager.memoryManagershutdown();
	Messages.messageSystemShutdown();
	Renderer.renderingShutdown();
}


/*Memorymanager::StackAllocator* stackallocator = memorymanager.newAllocator(1000, alignof(int));*/
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