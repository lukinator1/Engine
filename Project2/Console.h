#pragma once
#include "Mathlibrary/vector2.h"
#include "SDL2/SDL.h"
#include "Messaging/Message.h"
#include "Rendering/Rendermanager.h"
#include "Input.h"
#include <string>
class Console
{
private:
	vector2 consoleposition;
	vector3 consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	float consoletextsize = 1.0f;
	Rendering* rendermanager;
	Input* inputs;
	Rendertext textrenderer;
	bool displayconsole = true;
	bool consolefocused = false;
	bool consoleon = true;
	bool consoleecho = true;
	const Uint8 *sdlkeyboard = SDL_GetKeyboardState(NULL);
public:
	void consoleUpdate();
	void interpretInput();
	void useConsole();
	void leaveConsole();
	bool consoleOn();
	void consoleStartup(Input &Inputs, Rendering &rendermanager);
	std::string consoleinput = "";
	std::string composition = "> ";
	bool consoleFocused();
	void echoConsole(bool echo);
	void displayConsole(bool display);
	void displayConsole(bool display, vector2 pos);
	void displayConsole(bool display, float x, float y);
	void setConsolePosition(vector2 pos);
	void handleMessage(Message &message);
	void postMessage(Message::Messagetypes message, int on);
	void setConsolePosition(float x, float y);
	void setConsoleColor(vector3 color);
	void setConsoleColor(float x, float y, float z);
	void setConsoleSize(float newsize);
	vector2 getConsolePosition();
	void setConsoleFont();

	Console();
	~Console();
};

