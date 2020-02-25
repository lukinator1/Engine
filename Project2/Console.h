#pragma once
#include "Mathlibrary/vector2.h"
#include "SDL2/SDL.h"
#include "Messaging/Message.h"
#include "Rendering/Rendermanager.h"
#include <string>
class Console
{
private:
	Rendering* rendermanager;
	void consoleUpdate();
	void useConsole();
	void leaveConsole();
	bool displayconsole = true;
	bool consolefocused = false;
	bool consoleecho = true;
	vector2 consoleposition;
	vector3 consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	float consoletextsize;
public:
	void consoleStartup(Rendering * rendermanager);
	std::string consoleinput;
	std::string composition;
	void consoleOn(bool on);
	void echoConsole(bool echo);
	void displayConsole(bool display);
	void displayConsole(bool display, vector2 pos);
	void displayConsole(bool display, float x, float y);
	void setConsolePosition(vector2 pos);
	void handleMessage(Message &message);
	void setConsolePosition(float x, float y);
	void setConsoleFont();
	void setConsoleColor();

	Console();
	~Console();
};

