#include <fstream>
#include <sstream>
#include "Engine.h"
#include "Thegame.h"
#include "Window.h"
#include "Input.h"
#include "Rendering/Rendering.h"
#include "Audio/Audiomanager.h"
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
Scene *currentscene;
std::vector<Physicsobject *> colliders;
float fieldDepth = 20.0f;
float fieldWidth = 20.0f;
void swapScene(Scene &scene) {
	currentscene->closeScene();
	currentscene = &scene;
	currentscene->initScene();
}
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

	Logger log;				//startup
	log.startUp();
	Memorymanager MemoryManager(sfsize, sfalignment, dbsize, dbalignment);
	Messagesystem Messages;
	Window Window(windowwidth, windowheight, title, windowicon, fullscreen, desktopfullscreen, borderless, vsync);
	Physicsmanager Physics;
	Rendering Renderer;
	Renderer.renderingStartup(Window);
	Audiomanager Audio;
	Audio.audioStartup();
	Camera Camera;
	Camera.cameraStartup(fov, maxviewdistance, minviewdistance, arwidth, arheight);
	Window.cameraptr = &Camera;
	Resourcemanager SS;
	Input Inputs;
	Inputs.inputStartup();
	Console Console;
	Console.consoleStartup(log, MemoryManager, Window, Inputs, Renderer, Physics, Camera, SS);

	//test scene
	Scene sceneone;		
	sceneone.setSkybox("right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg");
	Scene scenetwo;
	Scene scenethree;


	//lights
	sceneone.setAmbientLight(vector3(0.3f, 0.3f, 0.3f));
	SS.addDirectionalLight("dlight1", Directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.5f));
	SS.addDirectionalLight("dlight2", Directionallight(vector3(1.0f, 0, 0), vector3(-1.0f, 1.0f, -1.0f), 0.4f));
	SS.addPointLight("plight1", Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f));
	SS.addSpotLight("slight1", Spotlight(vector3(0.0f, 1.0f, 1.0f), vector3(5.0f, 0.0f, 5.0f), vector3(1.0f, -1.0f, 1.0f), 80.0f, 0.7f, 3.0f, 0.0f, 0.1f));
	SS.addPointLight("orangeplight", Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f));
	SS.addPointLight("blueplight", Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f));

	sceneone.addDirectionalLight(SS.getDirectionalLight("dlight1"));
	/*sceneone.addDirectionalLight(SS.getDirectionalLight("dlight2"));*/
	sceneone.addPointLight(SS.getPointLight("plight1"));
	sceneone.addSpotLight(SS.getSpotLight("slight1"));
	sceneone.addPointLight(SS.getPointLight("orangeplight"));
	sceneone.addPointLight(SS.getPointLight("blueplight"));

	//SS.addPointLight("plight3", Pointlight(vector3(1.0f, 0.2f, 0.0f), vector3(2.0f, 0.0f, 7.0f), 16.0f, 2.0f, 0.0f, 1.0f));
	//scenetwo.addPointLight(SS.getPointLight("plight3"));

	//meshes
	SS.addMaterials("mats1", Materials("test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f));
	SS.addMaterials("mats2", Materials("container.jpg", vector3(1.0f, 1.0f, 0.0f), 1.0f, 8.0f));
	SS.addMaterials("mats3", Materials("ashbringer_color_map.png", vector3(1.0f, 1.0f, 0.0f), 1.0f, 8.0f));

	//castle
	SS.addModel("Quote", Model("quote.obj"));
	/*SS.addModel("Cloud", Model("Cloud.obj"));
	SS.addModel("Snake", Model("snake1.obj"));
	SS.addModel("Mario", Model("mario.obj"));
	SS.addMesh("Cube", Mesh("cube.obj"));
	SS.addMesh("Sphere", Mesh("sphere.obj"));
	SS.addModel("Gumi", Model("gumi1.obj"));
	SS.addModel("Cube", Model("cube.obj"));
	SS.addModel("cardboardbox", Model("CardBoardBox.obj"));
	SS.addModel("Castle", Model("Peachs1 Castle 1f.obj"));*/

	//SS.addModel("Quote", Model(""));
	SS.addModel("Cloud", Model(""));
	SS.addModel("Snake", Model(""));
	SS.addModel("Mario", Model(""));
	SS.addMesh("Cube", Mesh(""));
	SS.addMesh("Sphere", Mesh(""));
	SS.addModel("Gumi", Model(""));
	SS.addModel("Cube", Model(""));
	SS.addModel("cardboardbox", Model(""));
	SS.addModel("Castle", Model(""));
	
	//valley
	/*(SS.addModel("Valleyoftrials", Model("Valleyoftrials.obj"));
	SS.addModel("2B", Model("Nier2b.obj"));
	SS.addModel("Ashebringer", Model("Ashebringer.obj"));
	SS.addModel("Altar", Model("Altar.obj"));*/
	SS.addModel("Valleyoftrials", Model(""));
	SS.addModel("2B", Model(""));
	SS.addModel("Ashebringer", Model(""));
	SS.addModel("Altar", Model(""));

	//temple
	/*SS.addModel("Floatingisland", Model("floatingisland.obj"));
	SS.addModel("Kirby", Model("Kirby.obj"));
	SS.addModel("Scout", Model("Scout2.obj"));
	SS.addModel("Rin Tezuka", Model("rin tezuka"));*/
	
	SS.addModel("Floatingisland", Model(""));
	SS.addModel("Kirby", Model(""));
	SS.addModel("Scout", Model(""));
	SS.addModel("Rin Tezuka", Model(""));

	//physics
	SS.addBoundingSphere("bsphere1", Boundingsphere());
	SS.addBoundingSphere("bsphere2", Boundingsphere());
	SS.addAABB("AABB1", Boundingbox());
	SS.addAABB("AABB2", Boundingbox());

	//audio
	Audioclip testclip;
	testclip.loadAudio("testClip.wav");
	Audioclip testcliptwo;
	testcliptwo.loadAudio("sample.wav");
	Audioclip castlewalls;
	castlewalls.loadAudio("Inside The Castle Walls by Smart Gaming _ Free Listening on SoundCloud - Google Chrome 2020-04-07 16-48-44_Trim.wav");
	Audioclip yoshis;
	yoshis.loadAudio("Yoshi's Athletic Theme.wav");
	Audioclip wii;
	wii.loadAudio("Wii Shop Channel.wav");

	sceneone.setCurrentSong(castlewalls);
	scenetwo.setCurrentSong(yoshis);
	scenethree.setCurrentSong(wii);

	//entites

	//sceneone
	Entity Quote("Quote"); 
	Quote.transform.setPosition(vector3(10.0f, 17.5f, 12.0f));
	/*Meshrenderer component(SS.getMesh("Quote"), SS.getMaterials("mats1"));*/
	Modelrenderer quotemodel(SS.getModel("Quote"));
	Quote.transform.Rotate(0.0f, 0.0f, 50.0f);
	Quote.transform.setRotation(0.0f, 0.0f, 0.0f, 0.0f);
	Quote.addComponent(&quotemodel);

	Entity Castle("Castle");
	Modelrenderer castlemodel(SS.getModel("Castle"));
	Castle.transform.setPosition(-15.0f, 3.0f, 6.0f);
	Castle.transform.setScale(vector3(40.0f, 40.0f, 40.0f));
	Castle.addComponent(&castlemodel);
	Quote.addSubEntity(&Castle);

	Entity Cloud("Cloud");
	Cloud.transform.setPosition(vector3(5.0f, 0.0f, 10.0f));
	Cloud.transform.setScale(vector3(0.10f, .10f, .10f));
	Modelrenderer cloudmodel(SS.getModel("Cloud"));
	Boundingspherecollider bspherecloud(SS.getBoundingSphere("bsphere1"));
	bspherecloud.boundingsphere.setColliderTransform(Cloud.transform);
	bspherecloud.boundingsphere.radius = 2.0f;
	bspherecloud.boundingsphere.mass = 20.0f;
	bspherecloud.boundingsphere.recalculateMOI();
	Cloud.addComponent(&cloudmodel);
	Cloud.addComponent(&bspherecloud);
	Quote.addSubEntity(&Cloud);

	Entity Snake("Snake");
	Snake.transform.setPosition(vector3(10.0f, -3.0f, 20.0f));
	Snake.transform.setScale(vector3(0.08f, 0.08f, 0.08f));
	Modelrenderer snakecomponent(SS.getModel("Snake"));
	Snake.addComponent(&snakecomponent);
	Cloud.addSubEntity(&Snake);

	Entity Mario("Mario");
	Mario.transform.setPosition(vector3(30.0f, 0.0f, 15.0f));
	Mario.transform.setScale(vector3(0.07f, 0.07f, 0.07f));
	Modelrenderer mariomodel(SS.getModel("Mario"));
	Mario.addComponent(&mariomodel);
	AABBcollider AABBmario(SS.getAABB("AABB1"));
	AABBmario.AABB.setPosition(Mario.transform.getPosition());
	AABBmario.AABB.mass = 40.0f;
	AABBmario.AABB.setWidth(2.0f);
	AABBmario.AABB.setHeight(2.0f);
	AABBmario.AABB.setLength(2.0f);
	AABBmario.AABB.recalculateMOI();
	Mario.addComponent(&AABBmario);
	Quote.addSubEntity(&Mario);

	Entity Gumi("Gumi");
	Modelrenderer gumimodel(SS.getModel("Gumi"));
	Gumi.transform.setPosition(-15.0f, 3.0f, 15.0f);
	Gumi.transform.setScale(vector3(0.75f, 0.75f, 0.75f));
	Gumi.addComponent(&gumimodel);
	/*Quote.addSubEntity(&Gumi);*/

	Entity sphereone("sphereone");  //physics tests, one getting hit
	sphereone.transform.setPosition(16.0f, 40.0f, -14.0f);
	sphereone.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	Meshrenderer spheremesh(SS.getMesh("Sphere"), SS.getMaterials("mats2"));
	sphereone.addComponent(&spheremesh);
	Boundingspherecollider sphereonecollider(SS.getBoundingSphere("bsphere1"));
	sphereonecollider.boundingsphere.setPosition(sphereone.transform.getPosition());
	sphereonecollider.boundingsphere.setRotation(sphereone.transform.getRotation());
	sphereonecollider.boundingsphere.radius = 2.0f;
	sphereonecollider.boundingsphere.mass = 36.0f;
	sphereonecollider.boundingsphere.recalculateMOI();
	sphereone.addComponent(&sphereonecollider);
	Quote.addSubEntity(&sphereone);

	Entity box1("AABBgettinghit");
	box1.transform.setPosition(7.5f, 40.0f, -14.0f);
	box1.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	Meshrenderer boxmesh1(SS.getMesh("Cube"), SS.getMaterials("mats2"));
	box1.addComponent(&boxmesh1);
	AABBcollider boxcollider1(SS.getAABB("AABB1"));
	boxcollider1.AABB.setPosition(box1.transform.getPosition());
	boxcollider1.AABB.setLength(4.0f);
	boxcollider1.AABB.setWidth(4.0f);
	boxcollider1.AABB.setHeight(4.0f);
	boxcollider1.AABB.recalculateMOI();
	box1.addComponent(&boxcollider1);
	Quote.addSubEntity(&box1);

	Entity box2("AABBdoinghitting"); //one doing hitting
	box2.transform.setPosition(7.5f, 40.0f, -26.0f);
	box2.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	Meshrenderer boxmesh2(SS.getMesh("Cube"), SS.getMaterials("mats1"));
	box2.addComponent(&boxmesh2);
	AABBcollider boxcollider2(SS.getAABB("AABB2"));
	boxcollider2.AABB.setPosition(box2.transform.getPosition());
	boxcollider2.AABB.setLength(4.0f);
	boxcollider2.AABB.setWidth(4.0f);
	boxcollider2.AABB.setHeight(4.0f);
	boxcollider2.AABB.recalculateMOI();
	box2.addComponent(&boxcollider2);
	Quote.addSubEntity(&box2);

	Entity spheretwo("spheretwo"); 
	spheretwo.transform.setPosition(16.0f, 40.0f, -26.0f);
	spheretwo.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	Meshrenderer otherspheremesh(SS.getMesh("Sphere"), SS.getMaterials("mats1"));
	spheretwo.addComponent(&otherspheremesh);
	Boundingspherecollider spheretwocollider(SS.getBoundingSphere("bsphere2"));
	spheretwocollider.boundingsphere.setColliderTransform(spheretwo.transform);
	spheretwocollider.boundingsphere.radius = 2.0f;
	spheretwocollider.boundingsphere.recalculateMOI();
	spheretwo.addComponent(&spheretwocollider);
	sphereone.addSubEntity(&spheretwo);

	Entity box("box");
	Meshrenderer boxmesh(SS.getMesh("Cube"), SS.getMaterials("mats2"));
	box.transform.setPosition(3, 6, 15);
	box.transform.setScale(vector3(2.0f, 2.0f, 2.0f));
	box.addComponent(&boxmesh);
	AABBcollider boxbox;
	boxbox.AABB.setColliderTransform(box.transform);
	boxbox.AABB.setHeight(4.0f);
	boxbox.AABB.setLength(4.0f);
	boxbox.AABB.setWidth(4.0f);
	box.addComponent(&boxbox);
	Quote.addSubEntity(&box);

	//scene two
	Entity valley("Valley of Trials");
	Modelrenderer valleymodel(SS.getModel("Valleyoftrials"));
	valley.addComponent(&valleymodel);

	Entity twoB("2B");
	Modelrenderer twoBmodel(SS.getModel("2B"));
	SS.getModel("2B").setMaterial(SS.getMaterials("mats1"));
	twoB.transform.setPosition(3.0f, 2.5f, 9.0f);
	twoB.transform.setScale(vector3(.3f, .3f, .3f));
	twoB.addComponent(&twoBmodel);
	valley.addSubEntity(&twoB);

	Entity Altar("Altar");
	Modelrenderer altarmodel(SS.getModel("Altar"));
	SS.getModel("Altar").setMaterial(SS.getMaterials("mats2"));
	Altar.transform.setPosition(-13.0f, 3.0f, 12.0f);
	Altar.transform.setScale(vector3(1.0f, 1.0f, 1.0f));
	Altar.addComponent(&altarmodel);
	valley.addSubEntity(&Altar);

	Entity Ashebringer("Ashebringer");
	Modelrenderer ashebringermodel(SS.getModel("Ashebringer"));
	SS.getModel("Ashebringer").setMaterial(SS.getMaterials("mats1"));
	Ashebringer.transform.setPosition(-13.0f, 6.0f, 0.0f);
	Altar.transform.setScale(vector3(1.2f, 1.2f, 1.2f));
	Altar.addComponent(&ashebringermodel);
	Altar.addSubEntity(&Ashebringer);

	
	//scene three
	Entity floatingisland("Floating Island");
	floatingisland.transform.setScale(25.0f, 25.0f, 25.0f);
	Modelrenderer floatingislandmodel(SS.getModel("Floatingisland"));
	floatingisland.addComponent(&floatingislandmodel);
	
	/*Entity Kirby("Kirby");
	Modelrenderer kirbymodel(SS.getModel("Kirby"));
	Kirby.transform.setPosition(vector3(-12.0f, 40.0f, 3.0f));
	Kirby.transform.setScale(0.08f, 0.08f, 0.08f);
	Kirby.addComponent(&kirbymodel);
	floatingisland.addSubEntity(&Kirby);

	Entity Scout("Scout");
	Modelrenderer scoutmodel(SS.getModel("Scout"));
	Scout.transform.setPosition(vector3(-12.0f, 40, 0));
	Scout.addComponent(&scoutmodel);
	Kirby.addSubEntity(&Scout);

	Entity Rintezuka("Rint Tezuka");
	Modelrenderer rinmodel(SS.getModel("Rin Tezuka"));
	Rintezuka.transform.setPosition(vector3(-6.0f, 30.0f, 0));
	Rintezuka.addComponent(&rinmodel);
	Scout.addSubEntity(&Rintezuka);

	/*Entity bellecour;
	Modelrenderer bellecourmodel(SS.getModel("Bellecour"));
	bellecour.transform.setPosition(vector3(9.0f, 40.0f, 0));
	bellecour.addComponent(&bellecourmodel);
	Scout.addSubEntity(&bellecour);*/

	Entity field;
	Vertex vertices[] = { Vertex(vector3(-fieldWidth, 0.0f, -fieldDepth), vector2(0.0f, 0.0f)),
						Vertex(vector3(-fieldWidth, 0.0f, fieldDepth * 3), vector2(0.0f, 1.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, -fieldDepth), vector2(1.0f, 0.0f)),
						Vertex(vector3(fieldWidth * 3, 0.0f, fieldDepth * 3), vector2(1.0f, 1.0f)) };
	int indices[] = { 0, 1, 2,
					  2, 1, 3 };
	for (int i = 0; i < (sizeof(indices) / sizeof(indices[0])); i += 3) {
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];
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
	field.transform.setPosition(vector3(0, 0, 0));
	field.addComponent(&fieldcomponent);
	AABBcollider fieldbox;
	fieldbox.AABB.setColliderTransform(field.transform);
	fieldbox.AABB.setHeight(10.0f);
	fieldbox.AABB.setLength(10.0f);
	fieldbox.AABB.setWidth(10.0f);
	fieldbox.AABB.setMass(80.0f);
	fieldbox.AABB.recalculateMOI();
	//field.addComponent(&fieldbox);
	Quote.addSubEntity(&field);

	sceneone.setRoot(&field);
	scenetwo.setRoot(&valley);
	scenethree.setRoot(&floatingisland);

	currentscene = &sceneone;
	sceneone.initScene();
	/*Spotlight flashlight(vector3(0.0f, 1.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	Pointlight *plights = new Pointlight[6];
	plights[0] = Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f);
	plights[1] = Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f);
	shaderit.getPointLights()[0] = &plights[0];
	shaderit.getPointLights()[1] = &plights[1];
	shaderit.pointlight = plights[1];
	Spotlight *slights = new Spotlight[1];
	slights[0] = Spotlight(vector3(0.6f, 0.0f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), vector3(1.0f, 1.0f, 1.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
	shaderit.getSpotLights()[0] = &flashlight;*/

	//time calculation
	int prevtimecounter = 0;
	float prevdeltatimes[5] = { 1.0f / 60.0f,  1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f, 1.0f / 60.0f };
	std::chrono::high_resolution_clock::time_point starttime;
	std::chrono::high_resolution_clock::time_point endtime;
	std::chrono::duration<float> timeduration;
	std::chrono::duration<float> chronodelta = std::chrono::duration<float>(deltatime);
	
	//engine tools
	int frames = 0;
	double framecounter = 0;
	int fps = -1;
	bool fpscounter = true;

	//game variable tests
	Camera.setMouseLook(true);
	bool flashlighton = true;
	float unitest = 0.0f;
	void * currenttestphyobject[2] = { &bspherecloud, &AABBmario };
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
			if (Inputs.keyboardstate[Input::W].first == 1 && !Console.consoleOn()) {
			Camera.moveCamera(Camera.camerarotation.getForward(), deltatime * 20);	
			}
		if (Inputs.keyboardstate[Input::A].first == 1 && !Console.consoleOn()) {
			Camera.moveCamera(Camera.camerarotation.getLeft(), deltatime * 20);
		}
		if (Inputs.keyboardstate[Input::S].first == 1 && !Console.consoleOn()) {
			Camera.moveCamera(Camera.camerarotation.getBack(), (deltatime * 20));
		}
		if (Inputs.keyboardstate[Input::D].first == 1 && !Console.consoleOn()) {
			Camera.moveCamera(Camera.camerarotation.getRight(), (deltatime * 20));
		}
		if (Inputs.keyboardstate[Input::M].first == 1 && Inputs.keyboardstate[Input::M].second == 0) { 
			//testclip.playAudio();
			}
		if (Inputs.keyboardstate[Input::B].first == 1 && Inputs.keyboardstate[Input::B].second == 0) {
			testclip.endAudio();
		}
		if (Inputs.keyboardstate[Input::N].first == 1 && Inputs.keyboardstate[Input::N].second == 0) {
			//testcliptwo.playAudio();
		}
		if (Inputs.keyboardstate[Input::V].first == 1 && Inputs.keyboardstate[Input::V].second == 0) {
			testcliptwo.pauseAudio();
		}
		/*if (Inputs.keyboardstate[Input::C].first == 1 && Inputs.keyboardstate[Input::C].second == 0) {
			sceneone.currentsong.endAudio();
		}
		if (Inputs.keyboardstate[Input::X].first == 1 && Inputs.keyboardstate[Input::X].second == 0) {
			scenetwo.currentsong.endAudio();
		}*/
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
		if (Inputs.keyboardstate[Input::P].first == 1 && Inputs.keyboardstate[Input::P].second == 0 && !Console.consoleOn()) {  //flashlight 
			vector3 right(0, 0, 10.0f);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (right.z > 0) {
					right.z = -right.z;
				}
			}
			spheretwocollider.boundingsphere.velocity += right;
		}
		if (Inputs.keyboardstate[Input::L].first == 1 && Inputs.keyboardstate[Input::L].second == 0 && !Console.consoleOn()) {  //flashlight 
			vector3 right(0, 0, 10.0f);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (right.z > 0) {
					right.z = -right.z;
				}
			}
			boxcollider2.AABB.velocity += right;
		}
		if (Window.resized) {
			Camera.aspectratiowidth = Window.getWindowWidth();
			Camera.aspectratioheight = Window.getWindowHeight();
		}
		if (Inputs.keyboardstate[Input::I].first == true) {
			vector3 forward(0.1f, 0, 0);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (forward.x > 0) {
					forward.x = -forward.x;
				}
			}
			boxcollider2.AABB.acceleration += forward;
		}
		if (Inputs.keyboardstate[Input::J].first == true) {
			vector3 up(0, 0.1f, 0);
			if (Inputs.keyboardstate[Input::Rightshift].first) {
				if (up.y > 0) {
					up.y = -up.y;
			}
			}
			boxcollider2.AABB.acceleration += up;
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
			bspherecloud.boundingsphere.collidertransform.rotation = Quaternion(0, 0, 0, 1);
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
		if (Inputs.keyboardstate[Input::One].first == 1 && Inputs.keyboardstate[Input::One].second == 0) {
			swapScene(sceneone);
		}
		if (Inputs.keyboardstate[Input::Two].first == 1 && Inputs.keyboardstate[Input::Two].second == 0) {
			swapScene(scenetwo);
		}
		if (Inputs.keyboardstate[Input::Three].first == 1 && Inputs.keyboardstate[Input::Three].second == 0) {
			swapScene(scenethree);
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
		/*flashlight.setPosition(Camera.getCameraposition());
		flashlight.setDirection(Camera.camerarotation.getForward());
		shaderit.useShader();
		shaderit.
		(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, fieldmaterials);
		meshme.drawMesh();*/
		Physics.Update(*currentscene);
		Renderer.renderScene(*currentscene);
		Window.updateWindow();
		Audio.audioUpdate(*currentscene);
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
		//Window.updateWindow();
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