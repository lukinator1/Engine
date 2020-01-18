#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <algorithm>
#include <iostream>
#include "Messaging.h"
namespace Engine {
	class Window
	{
	private:
		int windowwidth;
		int windowheight;
		SDL_Window* window;
		SDL_GLContext glContext;
	public:
		void handleMessage(Message *message);
		Window(int width, int height, std::string title);
		virtual ~Window();
		void updateWindow();
		void setWindow(int width, int height);
		void setWindowIcon();
		void setWindowBordered(bool isbordered);
		void setFullscreen(bool fullscreen);
		void setFullscreen(bool fullscreen, bool desktop);
		int getWindowWidth(Window window);
		int getWindowHeight(Window window);
		void setWindow(int newwidth, int newheight, const char* newtitle);
	};
}
