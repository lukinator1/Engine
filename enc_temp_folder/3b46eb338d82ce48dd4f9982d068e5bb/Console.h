#pragma once
#include "Mathlibrary/vector2.h"
#include "SDL2/SDL.h"
#include "Messaging/Message.h"
#include "Rendering/Rendermanager.h"
#include "CustomMemoryAllocation/Memorymanager.h"
#include "Input.h"
#include <vector>
#include <string>
class Console
{
private:
	vector2 consoleposition;
	vector3 consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	float consoletextsize = 1.0f;
	float consolewidth = 0;
	Rendering* rendermanager;
	Logger* logger;
	Memorymanager* memorymanager;
	Window* window;
	Input* inputs;
	Camera* thecamera;
	Scene* currentscene;
	bool displayconsole = true;
	bool consolefocused = false;
	bool consoleon = false;
	bool consoleecho = true;
	const Uint8 *sdlkeyboard = SDL_GetKeyboardState(NULL);
public:
	void consoleUpdate(Scene &currentscene, bool &gameisrunning, bool &framebyframe, int &stepframekey, int &exitframekey, bool &fpscounter, bool &framelock, float &deltatime, float &dtime, float &deltatimeweight);
	void interpretInput(Scene &_currentscene, bool &gameisrunning, bool &framebyframe, int &stepframekey, int &exitframekey, bool &fpscounter, bool &framelock, float &deltatime, float &dtime, float &deltatimeweight);
	void useConsole();
	void leaveConsole();
	bool consoleOn();
	void consoleStartup(Logger &log, Memorymanager &memorymanager, Window &window, Input &Inputs, Rendering &rendermanager, Camera &camera);
	std::string consoleinput = "";
	std::string response = "";
	std::string composition = "> ";
	std::vector<std::string> oldcomposition;
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

