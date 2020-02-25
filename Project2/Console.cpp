#include "Console.h"
void Console::consoleStartup(Rendering &_rendermanager) {
	rendermanager = &_rendermanager;
	consoleposition = vector2(rendermanager->windowptr->getWindowWidth() * .8f, rendermanager->windowptr->getWindowHeight() * .8f);
	consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	consoletextsize = 1.0f;
	composition = ">";
	consoleinput = "";
}
void Console::consoleUpdate()
{
	if (displayconsole) {
			rendermanager->Textrenderer.renderText("> ", consoleposition.x , consoleposition.y, consoletextcolor, consoletextsize);
			textrenderer.renderText(">", 30.0f, 100.0f, vector3(1.0f, 1.0f, 1.0f), .4f);
	}
}
void Console::interpretInput() {
	if (consolefocused) {
		if (consoleinput == "test") {
			std::cout << "Console input detected" << std::endl;
		}
	}
	composition = "> ";
}
void Console::useConsole() {
	SDL_StartTextInput();
	consolefocused = true;
}
void Console::leaveConsole() {
	SDL_StopTextInput();
	consolefocused = false;
}
void Console::consoleOn(bool on)
{
	consolefocused = on;
}
void Console::echoConsole(bool echo)
{
	consoleecho = echo;
}
void Console::displayConsole(bool display)
{
	displayconsole = display;
}
void Console::displayConsole(bool display, vector2 pos)
{
	displayconsole = display;
	setConsolePosition(pos);
}
void Console::displayConsole(bool display, float x, float y)
{
	displayconsole = display;
	setConsolePosition(x, y);
}
void Console::setConsolePosition(vector2 pos)
{
	consoleposition = pos;
}
void Console::setConsolePosition(float x, float y)
{
	consoleposition.x = x;
	consoleposition.y = y;
}
void Console::setConsoleColor(vector3 color) {
	consoletextcolor = color;
}
void Console::setConsoleColor(float x, float y, float z) {
	consoletextcolor.x = x;
	consoletextcolor.y = y;
	consoletextcolor.z = z;
}
void Console::setConsoleSize(float newsize) {
	consoletextsize = newsize;
}
vector2 Console::getConsolePosition() {
	return consoleposition;
}
void Console::handleMessage(Message &message) {
	switch (message.messagetype)
	{
	case Message::Messagetypes::Textinput:
		composition.append(message.messagedatathree);
		break;
	case Message::Messagetypes::Textcommit:
		consoleinput = message.messagedatathree;
		interpretInput();
		break;
	}
}
Console::Console()
{
}
Console::~Console()
{
}
