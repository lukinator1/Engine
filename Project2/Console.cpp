#include "Console.h"
void Console::consoleStartup(Rendering * _rendermanager) {
	rendermanager = _rendermanager;
	consoleposition = vector2(rendermanager->windowptr->getWindowWidth(), rendermanager->windowptr->getWindowHeight());
}
void Console::consoleUpdate()
{
	if (consolefocused) {
		rendermanager->Textrenderer.renderText(">", consoleposition, consoletextcolor, consoletextsize);

	}
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
}
void Console::setConsolePosition(float x, float y)
{
}
void Console::handleMessage(Message &message) {
	switch (message.messagetype)
	{
	case Message::Messagetypes::Textinput:
		composition = message.messagedatathree;
		break;
	case Message::Messagetypes::Textcommit:
		consoleinput = message.messagedatathree;
	}
}

Console::Console()
{
}


Console::~Console()
{
}
