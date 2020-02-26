#include "Console.h"
void Console::consoleStartup(Input &_Inputs, Rendering &_rendermanager) {
	rendermanager = &_rendermanager;
	inputs = &_Inputs;
	consoleposition = vector2(rendermanager->windowptr->getWindowWidth() * .55f, rendermanager->windowptr->getWindowHeight() * .55f);
	consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	consoletextsize = 0.7f;
	composition = "> ";
	consoleinput = "";
	SDL_StopTextInput();
}
void Console::consoleUpdate()
{
	if (consoleon) {
			rendermanager->Textrenderer.renderText(composition, consoleposition.x , consoleposition.y, consoletextcolor, consoletextsize);
			if (consoleon && sdlkeyboard[40]) {
				interpretInput();
			} 
			/*textrenderer.renderText(">", 30.0f, 100.0f, vector3(1.0f, 1.0f, 1.0f), .4f);*/
	}
}
void Console::interpretInput() {
		if (composition == "> test") {
			std::cout << "Console input detected" << std::endl;
		}
		if (composition == "> tester") {
			rendermanager->Textrenderer.renderText("testing", 10, 20);
		}
		composition = "> ";
}
void Console::useConsole() {
	SDL_StartTextInput();
	/*inputs->consoleon = true;*/
	consoleon = true;
	displayconsole = true;
	consolefocused = true;
}
void Console::leaveConsole() {
	SDL_StopTextInput();
	/*inputs->consoleon = false;*/
	/*postMessage(Message::Messagetypes::Consoleoff, 1);*/
	consoleon = false;
	displayconsole = false;
	consolefocused = false;
}
bool Console::consoleOn() {
	return consoleon;
}
bool Console::consoleFocused()
{
	return consolefocused;
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
		/*case Message::Messagetypes::Textinput:
			composition.append(message.messagedatathree);
			break;*/
	case Message::Messagetypes::Textcommit:
		if (consoleon == true) {
			composition.append(message.messagedatathree);
		}
		/*interpretInput();*/
		break;
		}
}
void Console::postMessage(Message::Messagetypes message, int on) {
	if (messagequeue.size() < messagequeuecapacity) {
		Message newmessage(message, Message::Category::Console);
		newmessage.messagedataone = on;
		messagequeue.push(newmessage);
	}
}
Console::Console()
{
}
Console::~Console()
{
}
