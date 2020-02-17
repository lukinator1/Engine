#pragma once
#include <queue>
#include <chrono>
#include <ctime>
#include <ratio>
#include <thread>
#include <map>
#include "Window.h"
#include "Input.h"
#include "Rendering/Rendering.h"
#include "Mathlibrary/Mathlibrary.h"
#include "CustomMemoryAllocation/Memorymanager.h"
#include "Messaging/Messaging.h"
#include "Meshrenderer.h"
#include "Scene.h"
#include "Logger.h"
#include <GL/glew.h>
/*namespace SS {
	class Engine {
	private:
		float deltatime = 1.0f / 60.0f;
		float gametime = 0.0f;
		std::chrono::high_resolution_clock::time_point starttime;
		std::chrono::high_resolution_clock::time_point endtime;
		std::chrono::duration<double> timeduration;
		std::chrono::duration<double> chronodelta = std::chrono::duration<double>(deltatime);
		std::map<std::string, Scene> allscenes;
	public:
		Messaging Messages;
		Window window;
		Memorymanager memorymanager;
		Input Inputs;
		Camera thecamera;
		Transforming transform;
		Engine() {
			Startup();
		};
		~Engine() {
			ShutDown();
		}
		void loadScene(Scene);
		void loadScene(std::string filename);
		void Startup();
		void Update();
		void ShutDown();
	};*
}*/