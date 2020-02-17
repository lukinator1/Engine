#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <algorithm>
#include <iostream>
#include "Global.h"
#include "Messaging/Message.h"
//to do: window icon + resolution
//momerykl monkeyr
class Window
{
private:
	int windowwidth;
	int windowheight;
	SDL_GLContext glContext;
public:
	SDL_Window* window;
	void handleMessage(Message &message);
	void swapWindow();
	Window(int width, int height, std::string title);
	Window();
	virtual ~Window();
	void postMessage(Message message);
	/*void postMessage(Message::Messagetypes messagetype, int dataone, int datatwo);*/
	void updateWindow();
	void clearWindow(float r, float g, float b, float a);
	void setWindow(int width, int height);
	void setWindowIcon();
	void setWindowBordered(bool isbordered);
	void setFullscreen(bool fullscreen);
	void setFullscreen(bool fullscreen, bool desktop);
	int getWindowWidth();
	int getWindowHeight();
	void setWindow(int newwidth, int newheight, const char* newtitle);
};
