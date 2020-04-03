#include <fstream>
#include <sstream>
#include "Engine.h"
#include "Thegame.h"
#include "Window.h"
#include "Input.h"
#include "Rendering/Rendering.h"
#include "Mathlibrary/Mathlibrary.h"
#include "CustomMemoryAllocation/Memorymanager.h"
#include "Resourcemanager.h"
#include "Messaging/Messagesystem.h"
#include "Messaging/Messaging.h"
#include "Components/Components.h"
#include "Textrenderer.h"
#include "Scene.h"
#include "Logger.h"
#include "Global.h"
#include "Physics/Physics.h"
#include "Console.h"
#undef main
#include <iostream>
std::queue <Message> messagequeue;
int messagequeuecapacity = 32;
float deltatime = 1.0f / 60.0f;
float deltatimeweight = 1.0f;
float gametime = 0.0f;
bool gameisrunning = true;
bool framebyframe = false;
bool stepframe = false;
bool framekeyheld = false;
int stepframekey = 225;
int exitframekey = 41;
std::vector<Physicsobject *> colliders;

float fieldDepth = 10.0f;
float fieldWidth = 10.0f;

void endGame() {
	gameisrunning = false;
}
void frameByFrame(int stepkey, int exitkey) {
	if (framebyframe) {
		framebyframe = false;
		stepframekey = 225;
		exitframekey = 41;
	}
	else {
		framebyframe = true; 
		stepframekey = stepkey;
		exitframekey = exitkey;
	}
	stepframe = false;
	framekeyheld = false;
}
void frameByFrame() {
	if (framebyframe) {
		framebyframe = false;
	}
	else {
		framebyframe = true;
	}
	stepframekey = 225;
	exitframekey = 41;
	stepframe = false;
	framekeyheld = false;
}
int main(int argc, char* argv[]) {
		int count = 0;
		int sfsize = 500;  //settting configurations
		int sfalignment = 8;
		int dbsize = 500;
		int dbalignment = 8;
		bool framelock = false;
		float dtime = 1.0f / 60.0f;
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
					dtime = deltatime;
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
	Physicsmanager Physics;
	Rendering Renderer;
	Renderer.renderingStartup(Window);
	Resourcemanager SS;
	Camera Camera;
	Camera.cameraStartup(fov, maxviewdistance, minviewdistance, arwidth, arheight);
	Transforming transform;
	Input Inputs;
	Inputs.inputStartup();
	Console Console;
	Console.consoleStartup(log, MemoryManager, Window, Inputs, Renderer, Camera);

	/*Materials material("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);		// from basicshader change to render manager startup?
	Materials othermat("container.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);
	Mesh quotemodel("quote.obj");
	Mesh cloudmodel("Cloud.obj");
	Mesh snakemodel("snake.obj");
	Mesh scoutmodel("scout.obj");
	Mesh rinmodel("cube.obj");*/

	//test scene
	Scene sceneone;		
	sceneone.setSkybox("right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg");

	//lights
	sceneone.setAmbientLight(vector3(0.3f, 0.3f, 0.3f));
	SS.addDirectionalLight("dlight1", Directionallight(vector3(0, 0, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.4f));
	SS.addDirectionalLight("dlight2", Directionallight(vector3(1.0f, 0, 0), vector3(-1.0f, 1.0f, -1.0f), 0.4f));
	SS.addPointLight("plight1", Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f));
	SS.addSpotLight("slight1", Spotlight(vector3(0.0f, 1.0f, 1.0f), vector3(5.0f, 0.0f, 5.0f), vector3(1.0f, -1.0f, 1.0f), 80.0f, 0.7f, 3.0f, 0.0f, 0.1f));
	SS.addPointLight("orangeplight", Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f));
	SS.addPointLight("blueplight", Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f));

	sceneone.addDirectionalLight(SS.getDirectionalLight("dlight1"));
	sceneone.addDirectionalLight(SS.getDirectionalLight("dlight2"));
	sceneone.addPointLight(SS.getPointLight("plight1"));
	sceneone.addSpotLight(SS.getSpotLight("slight1"));
	sceneone.addPointLight(SS.getPointLight("orangeplight"));
	sceneone.addPointLight(SS.getPointLight("blueplight"));

	//meshes
	SS.addMaterials("mats1", Materials("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f));
	SS.addMaterials("mats2", Materials("container.jpg", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f));
	SS.addMesh("Quote", Mesh("quote.obj"));
	SS.addMesh("Cloud", Mesh("Cloud.obj"));
	SS.addMesh("Snake", Mesh("snake.obj"));
	SS.addMesh("Scout", Mesh("mario.obj"));
	SS.addMesh("Cube", Mesh("cube.obj"));
	SS.addMesh("Sphere", Mesh("sphere.obj"));
	SS.addMesh("Lovebox", Mesh("Peachs Castle 1f.obj"));
	SS.addMesh("cardboardbox", Mesh("CardBoardBox.obj"));
	SS.addModel("Castle", Model("Peachs Castle 1F.obj"));
	SS.addMesh("Castle", Mesh("Peachs Castle 1F.obj"));


	//physics
	SS.addBoundingSphere("bsphere1", Boundingsphere());
	SS.addBoundingSphere("bsphere2", Boundingsphere());

	//entites
	Entity Quote; 
	Quote.transform.setPosition(vector3(10.0f, 17.5f, 12.0f));
	Meshrenderer component(SS.getMesh("Quote"), SS.getMaterials("mats1"));
	Quote.transform.Rotate(0.0f, 0.0f, 50.0f);
	Quote.transform.setRotation(0.0f, 0.0f, 0.0f, 0.0f);
	Quote.addComponent(&component);

	Meshrenderer otherspheremesh(SS.getMesh("Sphere"), SS.getMaterials("mats1"));
	Entity Cloud;
	Cloud.transform.setPosition(vector3(5.0f, 0.0f, 10.0f));
	/*Cloud.transform.setScale(vector3(0.05f, 0.05f, 0.05f));*/
	Cloud.transform.setScale(vector3(2.05f, 2.0f, 2.0f));
	Meshrenderer cloudcomponent(SS.getMesh("Cloud"), SS.getMaterials("mats2"));
	Boundingspherecollider bspherecloud(SS.getBoundingSphere("bsphere1"));
	bspherecloud.boundingsphere.setColliderTransform(Cloud.transform);
	bspherecloud.boundingsphere.radius = 2.0f;
	bspherecloud.boundingsphere.mass = 20.0f;
	bspherecloud.boundingsphere.recalculateMOI();
	/*Cloud.addComponent(&cloudcomponent);*/
	Cloud.addComponent(&otherspheremesh);
	Cloud.addComponent(&bspherecloud);
	Quote.addSubEntity(&Cloud);

	Entity Snake;
	Snake.transform.setPosition(vector3(10.0f, -3.0f, 20.0f));
	Snake.transform.setScale(vector3(0.08f, 0.08f, 0.08f));
	Meshrenderer snakecomponent(SS.getMesh("Snake"), SS.getMaterials("mats1"));
	Snake.addComponent(&snakecomponent);
	Cloud.addSubEntity(&Snake);

	Entity Scout;
	Scout.transform.setPosition(vector3(30.0f, 0.0f, 15.0f));
	Scout.transform.setScale(vector3(0.07f, 0.07f, 0.07f));
	Meshrenderer scoutcomponent(SS.getMesh("Scout"),SS.getMaterials("mats2"));
	Scout.addComponent(&scoutcomponent);
	Snake.addSubEntity(&Scout);

	Entity Rintezuka;
	Rintezuka.transform.setPosition(vector3(15.0f, 0.0f, 15.0f));
	Rintezuka.transform.setScale(vector3(0.07f, 0.07f, 0.07f));
	Meshrenderer rincomponent(SS.getMesh("Cube"), SS.getMaterials("mats1"));
	Rintezuka.addComponent(&rincomponent);
	Scout.addSubEntity(&Rintezuka);

	Entity sphereone;
	sphereone.transform.setPosition(7.5f, 40.0f, -14.0f);
	sphereone.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	Meshrenderer spheremesh(SS.getMesh("Sphere"), SS.getMaterials("mats2"));
	sphereone.addComponent(&spheremesh);
	Boundingspherecollider sphereonecollider(SS.getBoundingSphere("bsphere1"));
	sphereonecollider.boundingsphere.setPosition(sphereone.transform.getPosition());
	sphereonecollider.boundingsphere.setRotation(sphereone.transform.getRotation());
	sphereonecollider.boundingsphere.radius = 2.0f;
	sphereonecollider.boundingsphere.mass = 7.0f;
	/*sphereonecollider.boundingsphere.recalculateMOI();*/
	sphereone.addComponent(&sphereonecollider);
	Rintezuka.addSubEntity(&sphereone);

	Entity spheretwo;
	spheretwo.transform.setPosition(7.5f, 40.0f, -21.0f);
	spheretwo.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	spheretwo.addComponent(&otherspheremesh);
	Boundingspherecollider spheretwocollider(SS.getBoundingSphere("bsphere2"));
	spheretwocollider.boundingsphere.setColliderTransform(spheretwo.transform);
	spheretwocollider.boundingsphere.radius = 2.0f;
	sphereonecollider.boundingsphere.mass = 36.0f;
	/*sphereonecollider.boundingsphere.recalculateMOI();*/
	spheretwo.addComponent(&spheretwocollider);
	sphereone.addSubEntity(&spheretwo);

	/*Entity lovebox;
	Meshrenderer loveboxmesh(SS.getMesh("Lovebox"), SS.getMaterials("mats2"));
	lovebox.transform.setPosition(0, 3.0f, 17.0f);
	lovebox.transform.setScale(vector3(5.0f, 5.0f, 5.0f));
	lovebox.addComponent(&loveboxmesh);
	sphereone.addSubEntity(&lovebox);
	AABBcollider loveboxbox;
	loveboxbox.boundingbox.setColliderTransform(lovebox.transform);
	loveboxbox.boundingbox.setHeight(0.1f);
	loveboxbox.boundingbox.setLength(10.0f);
	loveboxbox.boundingbox.setWidth(10.0f);
	loveboxbox.boundingbox.velocity.y = -3.0f;*/

	Entity box;
	Meshrenderer boxmesh(SS.getMesh("Cube"), SS.getMaterials("mats2"));
	box.transform.setPosition(0, 3.0f, 17.0f);
	box.transform.setScale(vector3(5.0f, 3.0f, 3.0f));
	box.addComponent(&boxmesh);
	sphereone.addSubEntity(&box);
	AABBcollider boxbox;
	boxbox.boundingbox.setColliderTransform(box.transform);
	boxbox.boundingbox.setHeight(0.1f);
	boxbox.boundingbox.setLength(10.0f);
	boxbox.boundingbox.setWidth(10.0f);

	Entity Castle;
	Modelrenderer castlemodel(SS.getModel("Castle"));
	/*Meshrenderer castlemesh(SS.getMesh("Castle"), SS.getMaterials("mats2"));*/
	Castle.transform.setPosition(-15.0f, 3.0f, 6.0f);
	Castle.transform.setScale(vector3(40.0f, 40.0f, 40.0f));
	Castle.addComponent(&castlemodel);
	/*Castle.addComponent(&castlemesh);*/
	Scout.addSubEntity(&Castle);

	Entity field;
	Vertex vertices[] = { Vertex(vector3(-fieldWidth, 0.0f, -fieldDepth), vector2(0.0f, 0.0f)),
						Vertex(vector3(-fieldWidth, 0.0f, fieldDepth * 3), vector2(0.0f, 1.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, -fieldDepth), vector2(1.0f, 0.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, fieldDepth * 3), vector2(1.0f, 1.0f)) };
	unsigned int indices[] = { 0, 1, 2,
					  2, 1, 3 };
	for (unsigned int i = 0; i < (sizeof(indices) / sizeof(indices[0])); i += 3) {
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];
		vector3 edge1 = vertices[i1].position.Subtract(vertices[i0].position);
		vector3 edge2 = vertices[i2].position.Subtract(vertices[i0].position);
		vector3 normal = (edge1.crossProduct(edge2)).Normalize();

		vertices[i0].normal = vertices[i0].normal.add(normal);
		vertices[i1].normal = vertices[i1].normal.add(normal);
		vertices[i2].normal = vertices[i2].normal.add(normal);
	}
	for (int i = 0; i < (sizeof(vertices) / sizeof(vertices[0])); i++) {
		vertices[i].normal = (vertices[i].normal).Normalize();
	}
	Materials fieldmaterials("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);
	Mesh meshme(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
	Meshrenderer fieldcomponent(meshme, fieldmaterials);
	field.transform.setPosition(vector3(0.0f, -1.0f, 5.0f));
	field.addComponent(&fieldcomponent);
	AABBcollider fieldbox;
	fieldbox.boundingbox.setColliderTransform(field.transform);
	fieldbox.boundingbox.setHeight(0.1f);
	fieldbox.boundingbox.setLength(10.0f);
	fieldbox.boundingbox.setWidth(10.0f);
	fieldbox.boundingbox.setMass(80.0f);
	fieldbox.boundingbox.recalculateMOI();
	Cloud.addSubEntity(&field);

	sceneone.setRoot(Quote);
	sceneone.initScene();
	
	//shaders
	/*Shader shaderit("phong");
	shaderit.setAmbientLight(vector3(0.5f, 0.5f, 0.5f));
	shaderit.directionallight = Directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.1f);*/

	//lights
	Spotlight flashlight(vector3(0.0f, 1.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	Pointlight *plights = new Pointlight[6];
	plights[0] = Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f);
	plights[1] = Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f);
	/*shaderit.getPointLights()[0] = &plights[0];
	shaderit.getPointLights()[1] = &plights[1];
	shaderit.pointlight = plights[1];
	Spotlight *slights = new Spotlight[1];
	slights[0] = Spotlight(vector3(0.6f, 0.0f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), vector3(1.0f, 1.0f, 1.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	/*shaderit.getSpotLights()[0] = &flashlight;*/

	//time calculation
	int prevtimecounter = 0;
	float prevdeltatimes[5] = { 1.0f / 60.0f,  1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f };
	std::chrono::high_resolution_clock::time_point starttime;
	std::chrono::high_resolution_clock::time_point endtime;
	std::chrono::duration<float> timeduration;
	std::chrono::duration<float> chronodelta = std::chrono::duration<float>(deltatime);
	
	//engine tools
	Scene *currentscene; 
	currentscene = &sceneone;
	int frames = 0;
	double framecounter = 0;
	int fps = -1;
	bool fpscounter = true;

	//game variable tests
	Camera.setMouseLook(true);
	bool flashlighton = true;
	float unitest = 0.0f;
	bool held = false;

	//loop
	while (gameisrunning) {
		while (framebyframe) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_KEYDOWN) {
					if (SDL_GetScancodeFromKey(event.key.keysym.sym) == stepframekey) {
						stepframe = true;
						if (event.key.repeat == 1) {
							framekeyheld = true;
						}
						break;
					}
					else if (SDL_GetScancodeFromKey(event.key.keysym.sym) == exitframekey) {
						frameByFrame();
						break;
					}
				}
				else if (event.type == SDL_KEYUP) {
					if (SDL_GetScancodeFromKey(event.key.keysym.sym) == stepframekey) {
						framekeyheld = false;
						break;
					}
				}
			}
			if (framekeyheld == true && Inputs.sdlkeyboard[41]) {
				break;
			}
			if (stepframe == true) {
				stepframe = false;
				break;
			}
		}
		starttime = std::chrono::high_resolution_clock::now();     //updates
		MemoryManager.memorymanagerUpdate();
		Inputs.getInputs();

		//game
		/*Camera.setCameraPosition(vector3(Cloud.transform.position.x, Cloud.transform.position.y, Cloud.transform.position.z - 7.5));
		Camera.cameraposition = vector3(bspherecloud.boundingsphere.collidertransform.position.x, bspherecloud.boundingsphere.collidertransform.position.y + 5.0f, bspherecloud.boundingsphere.collidertransform.position.z - 10.0f);*/
		bspherecloud.boundingsphere.velocity = vector3(0, 0, 0);
			if (Inputs.keyboardstate[Input::W].first == 1) {
			Camera.moveCamera(Camera.camerarotation.getForward(), deltatime * 20);	
			/*bspherecloud.boundingsphere.acceleration += (Camera.camerarotation.getForward().divide(650.0f));*/
			/*bspherecloud.boundingsphere.collidertransform.position.z = Camera.cameraposition.z + 7.5;
			bspherecloud.boundingsphere.collidertransform.position.y = Camera.cameraposition.y - 5.5;*/
			}
		if (Inputs.keyboardstate[Input::A].first == 1) {
			Camera.moveCamera(Camera.camerarotation.getLeft(), deltatime * 20);
			/*bspherecloud.boundingsphere.acceleration += (Camera.camerarotation.getLeft().divide(650.0f));
			bspherecloud.boundingsphere.collidertransform.position.x -= deltatime * 20;*/
		}
		if (Inputs.keyboardstate[Input::S].first == 1) {
			Camera.moveCamera(Camera.camerarotation.getBack(), (deltatime * 20));
			/*bspherecloud.boundingsphere.acceleration += (Camera.camerarotation.getBack().divide(650.0f));
			bspherecloud.boundingsphere.collidertransform.position.z -= deltatime * 20;*/
		}
		if (Inputs.keyboardstate[Input::D].first == 1) {
			Camera.moveCamera(Camera.camerarotation.getRight(), (deltatime * 20));
			/*bspherecloud.boundingsphere.acceleration += (Camera.camerarotation.getRight().divide(650.0f));
			bspherecloud.boundingsphere.collidertransform.position.x += deltatime * 20;*/
		}
		if (Inputs.keyboardstate[Input::Keyup].first == 1) {
			bspherecloud.boundingsphere.velocity = (Camera.camerarotation.getForward().multiply(50.0f));
		}
		if (Inputs.keyboardstate[Input::Keyleft].first == 1) {
			bspherecloud.boundingsphere.velocity = (Camera.camerarotation.getLeft().multiply(13.0f));
		}
		if (Inputs.keyboardstate[Input::Keydown].first == 1) {
			bspherecloud.boundingsphere.velocity = (Camera.camerarotation.getBack().multiply(13.0f));
		}
		if (Inputs.keyboardstate[Input::Keyright].first == 1) {
			bspherecloud.boundingsphere.velocity += (Camera.camerarotation.getRight().multiply(13.0f));
		}
		if (Inputs.keyboardstate[Input::L].first == 1 && Inputs.keyboardstate[Input::L].second == 0) {  //flashlight 
				/*if (flashlighton == true) {
					flashlight.setIntensity(0.0f);
					flashlighton = false;
				}
				else if (flashlighton == false) {
					flashlight.setIntensity(3.0f);
					flashlighton = true;
				}*/
			vector3 right(0, 0, 10.0f);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (right.z > 0) {
					right.z = -right.z;
				}
			}
		spheretwocollider.boundingsphere.velocity += right;
		}
		if (Inputs.keyboardstate[Input::I].first == true) {
			vector3 forward(0.1f, 0, 0);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (forward.x > 0) {
					forward.x = -forward.x;
				}
			}
			spheretwocollider.boundingsphere.acceleration += forward;
		}
		if (Inputs.keyboardstate[Input::J].first == true) {
			vector3 up(0, 0.1f, 0);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (up.y > 0) {
					up.y = -up.y;
			}
			}
			spheretwocollider.boundingsphere.acceleration += up;
		}
		if (Inputs.leftmouse.first == true) {
			if (held) {
				held = false;
			}
			else {
				held = true;
			}
			/*bspherecloud.boundingsphere.acceleration = vector3(0, 0, 0);
			bspherecloud.boundingsphere.angularvelocity = vector3(0, 0, 0);
			bspherecloud.boundingsphere.velocity = vector3(0, 0, 0);
			bspherecloud.boundingsphere.setPosition(Camera.cameraposition);*/
		}
		if (held) {
			bspherecloud.boundingsphere.acceleration = vector3(0, 0, 0);
			bspherecloud.boundingsphere.angularvelocity = vector3(0, 0, 0);
			bspherecloud.boundingsphere.velocity = vector3(0, 0, 0);
			bspherecloud.boundingsphere.setPosition(Camera.cameraposition.add(Camera.camerarotation.getForward().multiply(7.0f)));
		}
		if (Inputs.getScrolldistance().y != 0) {
			Camera.Zoom(Inputs.getScrolldistance().y);
		}
		if (Inputs.getMouseMovementDistance().x != 0 || Inputs.getMouseMovementDistance().y != 0) {
			Camera.rotateCamera(Inputs.getXMouseMovementDistance(), Inputs.getYMouseMovementDistance());
			/*bspherecloud.boundingsphere.setPosition(Camera.cameraposition.add(Camera.camerarotation.getForward().multiply(7.0f))); 
			/*bspherecloud.boundingsphere.collidertransform.position = Camera.cameraposition.add(Camera.camerarotation.getForward().multiply(13.0f));
			bspherecloud.boundingsphere.velocity.x = Inputs.getXMouseMovementDistance() * 20.0f;
			bspherecloud.boundingsphere.velocity.y = Inputs.getYMouseMovementDistance() * 20.0f;*/
		}
		if (Inputs.keyboardstate[Input::Grave].first == 1 && Inputs.keyboardstate[Input::Grave].second == 0) {
			if (!Console.consoleOn()) {
				Console.useConsole();
			}
			else if (Console.consoleOn())
			{
				Console.leaveConsole();
			}
		}
		if (Window.closeRequested() == true) {
			endGame();
		}

		//enginetests
		/*transform.setPosition(vector3(0.0f, -1.0f, 5.0f));
		plights[0].setPosition(vector3(3.0f, 0.0f, 8.0 * (float)(sin(unitest) + 1.0f / 2.0f) + 10.0f));
		plights[1].setPosition(vector3(7.0f, 0.0f, 8.0 * (float)(cos(unitest) + 1.0f / 2.0f) + 10.0f));*/
		SS.getPointLight("orangeplight").setPosition(vector3(3.0f, 0.0f, 8.0 * (float)(sin(unitest) + 1.0f / 2.0f) + 10.0f));
		SS.getPointLight("blueplight").setPosition(vector3(7.0f, 0.0f, 8.0 * (float)(cos(unitest) + 1.0f / 2.0f) + 10.0f));
		unitest += deltatime;
		flashlight.setPosition(Camera.getCameraposition());
		flashlight.setDirection(Camera.camerarotation.getForward());
		/*shaderit.useShader();
		shaderit.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, fieldmaterials);
		meshme.drawMesh();*/
		Physics.Update(*currentscene);
		Renderer.renderScene(*currentscene);
		/*text.renderComponent(transform, shaderit);*/     //interesting effect
		Console.consoleUpdate(*currentscene, gameisrunning, framebyframe, stepframekey, exitframekey, framelock, fpscounter, deltatime, dtime, deltatimeweight);
		frames++;
		if (framecounter >= 1.0f) {
			fps = frames;
			framecounter = 0;
			frames = 0;
		}
		if (fpscounter == true) {
			Renderer.Textrenderer.renderText("Delta time: " + std::to_string(deltatime), 0, Window.getWindowHeight() * .5f, vector3(1.0f, 1.0f, 1.0f), 0.7);
			if (fps == -1) {
				Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, Window.getWindowHeight() * (3.0f / 4.0f), vector3(0.0, 0.0f, 0.0), 1.0);
			}
			if (fps < 30) {
				Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, Window.getWindowHeight() * (3.0f / 4.0f), vector3(1.0f, 0, 0), 1.0);
			}
			else if (fps < 50) {
				Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, Window.getWindowHeight() * (3.0f / 4.0f), vector3(0.7f, 0.1f, 0.4f), 1.0);
			}
			else if (fps < 90) {
				Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, Window.getWindowHeight() * (3.0f / 4.0f), vector3(1.0f, 1.0f, 1.0f), 1.0);
			}
			else if (fps < 120) {
				Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, Window.getWindowHeight() * (3.0f / 4.0f), vector3(0.0, 0.5f, 0.0), 1.0);
			}
			else {
				Renderer.Textrenderer.renderText("FPS: " + std::to_string(fps), 0, Window.getWindowHeight() * (3.0f / 4.0f), vector3(0.0, 1.0f, 0.0), 1.0);
			}
		}
		/*Renderer.Textrenderer.renderText("texter", 510.0f,  300.0f, vector3(1.0f, 1.0f, 1.0f), .4f);
		Renderer.Textrenderer.renderText("> The quick brown fox jumped over the lazy dog. 1234567890", 0.0f, 300.0f, vector3(0.4, 0.3, 0.8), .7f);*/
		Window.updateWindow();
		Messages.messageSystemUpdate(Inputs, Window, Camera, Console);



		//time calculations
		endtime = std::chrono::high_resolution_clock::now();
		timeduration = (endtime - starttime);
		if (framelock == false) {
			prevdeltatimes[prevtimecounter] = timeduration.count();
			prevtimecounter++;
			if (prevtimecounter == 5) {
				prevtimecounter = 0;
			}
			deltatime = (prevdeltatimes[0] + prevdeltatimes[1] + prevdeltatimes[2] + prevdeltatimes[3] + prevdeltatimes[4]) / 5.0f;
			if (deltatime > 2.0f) {
				deltatime = (1.0f / 6.0f);
			}
			framecounter += deltatime;
			deltatime *= deltatimeweight;
		}
		else if (framelock == true) {
			chronodelta = std::chrono::duration<float>(deltatime);
			if (timeduration.count() < chronodelta.count()) //framerate lock function
				{
					std::this_thread::sleep_for(chronodelta - timeduration);
					framecounter += deltatime;
				}
			else if (timeduration.count() > chronodelta.count()) {
				float totaldeltas = ((timeduration.count() / chronodelta.count()));
				if (totaldeltas > 20) {
					totaldeltas = 2;
				}
					float remain = remainder(timeduration.count(), chronodelta.count());
					totaldeltas -= remain;
				    std::this_thread::sleep_for(std::chrono::duration<float>( ((totaldeltas * chronodelta.count()) + chronodelta.count()) - timeduration.count() ));
					//std::this_thread::sleep_for(chronodelta - (timeduration - chronodelta)); //todo: change to division
					framecounter += ((totaldeltas + 1.0f) * chronodelta.count());
				}
			}
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