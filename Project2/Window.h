#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Global.h"
#include "Logger.h"
#include "Messaging/Message.h"
#include "Rendering/Texture.h"
//to do: desktop icon + resolution
//momerykl monkeyr
class Window : public Logger
{
private:
	int windowwidth;
	int windowheight;
	SDL_GLContext glContext;
	SDL_Window* window;
	void swapWindow();
	void clearWindow(float r, float g, float b, float a);
public:
	Window(int width, int height);
	Window(int width, int height, std::string title, std::string icon, bool fullscreen, bool desktopfullscreen, bool borderless, bool vsync);
	int getWindowWidth();
	int getWindowHeight();
	void updateWindow();
	void setWindow(int width, int height);
	void setWindow(int newwidth, int newheight, const char* newtitle);
	void setFullscreen(bool fullscreen);
	void setFullscreen(bool fullscreen, bool desktop);
	void setWindowBordered(bool isbordered);
	void setWindowIcon(std::string filename);
	void closeWindow();
	void postMessage(Message message);
	/*void postMessage(Message::Messagetypes messagetype, int dataone, int datatwo);*/
	void handleMessage(Message &message);
	~Window();
};
