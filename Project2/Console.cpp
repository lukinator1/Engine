#include "Console.h"
void Console::consoleStartup(Logger &_log, Memorymanager &_memorymanager, Window &_window, Input &_Inputs, Rendering &_rendermanager, Camera & _thecamera) {
	logger = &_log;
	memorymanager = &_memorymanager;
	window = &_window;
	rendermanager = &_rendermanager;
	inputs = &_Inputs;
	thecamera = &_thecamera;
	consoleposition = vector2(rendermanager->windowptr->getWindowWidth() * .55f, rendermanager->windowptr->getWindowHeight() * .55f);
	consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	consoletextsize = 0.3f;
	response = "";
	composition = "> ";
	consoleinput = "";
	SDL_StopTextInput();
}
void Console::consoleUpdate(Scene & _currentscene, bool &gameisrunning, bool &framebyframe, int &stepframekey, int &exitframekey, bool &framelock, bool &fpscounter)
{
	if (consoleon) {
			/*if (sdlkeyboard[42]) {
				if (composition.length() != 2) {
					composition.erase(composition.end() - 1);
				}
			}*/
		consolewidth = rendermanager->Textrenderer.renderText(composition, consoleposition.x, consoleposition.y, consoletextcolor, consoletextsize) + consoleposition.x;
		if (consolewidth > window->getWindowWidth()) {
			if (composition != "> ") {
				composition.erase(composition.size() - 1);
			consolewidth = rendermanager->Textrenderer.renderText(composition, consoleposition.x, consoleposition.y, consoletextcolor, consoletextsize);
			}
		}
		rendermanager->Textrenderer.renderText("_", consolewidth, consoleposition.y - 2.5f, consoletextcolor, consoletextsize);
			if (sdlkeyboard[40] && composition != "> ") {
				interpretInput(_currentscene, gameisrunning, framebyframe, stepframekey, exitframekey, framelock, fpscounter);
			}
		rendermanager->Textrenderer.renderText(response, consoleposition.x, consoleposition.y + 20.0f, consoletextcolor, consoletextsize);
	}
}
void Console::interpretInput(Scene &_currentscene, bool &gameisrunning, bool &framebyframe, int &stepframekey, int &exitframekey, bool &framelock, bool &fpscounter) {
	response = "";
	consoleinput = composition.substr(2, composition.length());
	if (consoleecho) {
		std::cout << consoleinput << std::endl;
	}
	//logger
	if (consoleinput.substr(0, 19) == "set logger channels") {
		std::vector<int> channels;
		if (consoleinput.length() >= 20) {
			for (int i = 19; i < consoleinput.length(); i++) {
				if (consoleinput[i] == '1' || consoleinput[i] == '2' || consoleinput[i] == '3' || consoleinput[i] == ' ') {
					if (consoleinput[i] == ' ') {
						continue;
					}
					else if (consoleinput[i - 1] != ' ') {
						channels.clear();
						break;
					}
					else if (i == consoleinput.length() - 1) {
						channels.push_back(consoleinput[i] - '0');
					}
					else if (consoleinput[i + 1] != ' ') {
						channels.clear();
						break;
					}
					else {
						channels.push_back(consoleinput[i] - '0');
					}
				}
				else {
					channels.clear();
					break;
				}
			}
		}
		if (channels.size() != 0) {
			for (int i = 0; i < channels.size(); i++) {
			logger->enginechannels[channels[i] - 1] = 1;
			response += std::to_string(channels[i]) + " ";
			}
			if (channels.size() == 1) {
				response = "Channel " + response + "is set.";
			}
			else{
				response = "Channels " + response + "are set.";
			}
		}
		else {
			response = "Error, please enter channels between 1 and 3.";
		}
	}
	else if (consoleinput.substr(0, 26) == "deactivate logger channels") {
		std::vector<int> channels;
		if (consoleinput.length() >= 28) {
			for (int i = 26; i < consoleinput.length(); i++) {
				if (consoleinput[i] == '1' || consoleinput[i] == '2' || consoleinput[i] == '3' || consoleinput[i] == ' ')  {
					if (consoleinput[i] == ' ') {
						continue;
					}
					else if (consoleinput[i - 1] != ' ') {
						channels.clear();
						break;
					}
					else if (i == consoleinput.length() - 1) {
						channels.push_back(consoleinput[i] - '0');
					}
					else if (consoleinput[i + 1] != ' '){
						channels.clear();
						break;
						}
					else {
						channels.push_back(consoleinput[i] - '0');
					}
				}
				else {
					channels.clear();
					break;
				}
			}
		}
		if (channels.size() != 0) {
			for (int i = 0; i < channels.size(); i++) {
				logger->enginechannels[channels[i] - 1] = 0;
				response += std::to_string(channels[i]) + " ";
			}
			if (channels.size() == 1) {
				response = "Channel " + response + "is deactivated.";
			}
			else {
				response = "Channels " + response + "are deactivated.";
			}
		}
		else {
			response = "Error, please enter channels between 1 and 3.";
		}
	}
	else if (consoleinput.substr(0, 20) == "set logger verbosity") {
		std::vector<int> verbosity;
		if (consoleinput.length() >= 22) {
			for (int i = 21; i < consoleinput.length(); i++) {
				if (consoleinput[i] == '1' || consoleinput[i] == '2' || consoleinput[i] == '3' || consoleinput[i] == ' ') {
					if (consoleinput[i] == ' '){
						continue;
					}
					else if (consoleinput[i - 1] != ' ') {
						verbosity.clear();
						break;
					}
					else if (i == consoleinput.length() - 1) {
						verbosity.push_back(consoleinput[i] - '0');
					}
					else if (consoleinput[i + 1] != ' ') {
						verbosity.clear();
						break;
					}
					else {
						verbosity.push_back(consoleinput[i] - '0');
					}
				}
				else {
					verbosity.clear();
					break;
				}
			}
			if (verbosity.size() == 1) {
				logger->engineverbosity = verbosity[0];
				response = "Verbosity set to " + std::to_string(logger->engineverbosity) + ".";
			}
			else {
				response = "Error, please enter a verbosity between 1 and 3.";
			}
		}
		else {
			response = "Error, please enter a verbosity between 1 and 3.";
		}
	}
	else if (consoleinput == "clear logs") {
		logger->clearLogs();
		response = "Logs cleared.";
	}	
	else if (consoleinput == "show logger warnings") {
	logger->showwarnings = true;
	response = "Logger warnings are on.";
	}
	else if (consoleinput == "hide logger warnings") {
	logger-> showwarnings = false;
	response = "Logger warnings are off";
	}

	

	//misc.
	else if (consoleinput == "framebyframe") { //todo
	framebyframe = true;
	response = "Framebyframe mode is on. Press leftshift to framestep, esc to exit.";
	}
	else if (consoleinput == "show fps counter") {
	fpscounter = true;
	response = "Fps counter displayed.";
	}
	else if (consoleinput == "hide fps counter") {
	fpscounter = false;
	response = "Fps counter hidden.";
	}
	else if (consoleinput.substr(0, 14) == "lock framerate") {
	framelock = true;
	response = "Framerate locked to ";
	}
	else if (consoleinput == "unlock framerate") {
	framelock = false;
	response = "Framerate unlocked.";
	}
	else if (consoleinput == "echo console") {
		if (consoleecho == true) {
			consoleecho = false;
			response = "Console echo is off.";
			std::cout << response << std::endl;
		}
		else if (consoleecho == false) {
			consoleecho = true;
			response = "Console is being echoed into the terminal.";
		}
	}
	else if (consoleinput == "exit") {
		gameisrunning = false;
		response = "Closing game. Goodbye!";
	}
	else {
		response = "Command " + consoleinput + " not found.";
	}

	if (consoleecho) {
		std::cout << response << std::endl;
	}
		consolewidth = 0;
		consoleinput = "";
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
	response = "";
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
	case Message::Messagetypes::Keydown:
		if (consoleon == true && message.messagedataone == 42 && composition != "> ") {
			composition.erase(composition.end() - 1);
		}
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
