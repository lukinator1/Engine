#include "Console.h"
#include "Global.h"
void Console::consoleStartup(Logger &_log, Memorymanager &_memorymanager, Window &_window, Input &_Inputs, Rendering &_rendermanager, Physicsmanager &_physicsmanager, Camera & _thecamera, Resourcemanager & SS) {
	logger = &_log;
	memorymanager = &_memorymanager;
	window = &_window;
	rendermanager = &_rendermanager;
	physicsmanager = &_physicsmanager;
	resourcemanager = &SS;
	inputs = &_Inputs;
	thecamera = &_thecamera;
	consoleposition = vector2(rendermanager->windowptr->getWindowWidth() * .40f, rendermanager->windowptr->getWindowHeight() * .55f);
	consoletextcolor = vector3(1.0f, 1.0f, 1.0f);
	consoletextsize = 0.25f;
	response = "";
	composition = "> ";
	consoleinput = "";
	SDL_StopTextInput();
}
void Console::consoleUpdate(Scene & _currentscene, bool &gameisrunning, bool &framebyframe, int &stepframekey, int &exitframekey, bool &framelock, bool &fpscounter, float &deltatime, float &dtime, float &deltatimeweight)
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
				interpretInput(_currentscene, gameisrunning, framebyframe, stepframekey, exitframekey, framelock, fpscounter, deltatime, dtime, deltatimeweight);
			}
		rendermanager->Textrenderer.renderText(response, consoleposition.x, consoleposition.y + 20.0f, consoletextcolor, consoletextsize);
	}
}
void Console::interpretInput(Scene &_currentscene, bool &gameisrunning, bool &framebyframe, int &stepframekey, int &exitframekey, bool &framelock, bool &fpscounter, float &deltatime, float& dtime, float &deltatimeweight) {
	response = "";
	consoleinput = composition.substr(2, composition.length());
	if (consoleecho) {
		std::cout << consoleinput << std::endl;
	}
	//logger
	if (consoleinput.substr(0, 19) == "set logger channels" && cheatson) {
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
	else if (consoleinput.substr(0, 26) == "deactivate logger channels" && cheatson) {
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
	else if (consoleinput.substr(0, 20) == "set logger verbosity" && cheatson) {
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
	else if (consoleinput == "clear logs" && cheatson) {
		logger->clearLogs();
		response = "Logs cleared.";
	}	
	else if (consoleinput == "show logger warnings" && cheatson) {
	logger->showwarnings = true;
	response = "Logger warnings are on.";
	}
	else if (consoleinput == "hide logger warnings" && cheatson) {
	logger-> showwarnings = false;
	response = "Logger warnings are off";
	}

	//window
	else if (consoleinput == "minimize") {
	response = "Window minimized.";
	SDL_MinimizeWindow(window->window);
	window->minimized = true;
	}
	else if (consoleinput == "maximize") {
	response = "Window maximized.";
	SDL_MaximizeWindow(window->window);
	window->maximized = true;
	}
	else if (consoleinput == "border window") {
	response = "Window borderered.";
	window->setWindowBordered(true);
	}
	else if (consoleinput == "unborder window") {
	response = "Windowed unbordered.";
	window->setWindowBordered(false);
	}
	else if (consoleinput == "fullscreen") {
	response = "Set to fulscreen mode.";
	window->setFullscreen(true);
	}
	else if (consoleinput == "fullscreen desktop") {
	response = "Set to fullscreen desktop mode.";
	window->setFullscreen(true, true);
	}
	else if (consoleinput == "windowed mode") {
	response = "Set to windowed mode.";
	window->setFullscreen(false);
	}


	//camera
	else if (consoleinput.substr(0, 7) == "set fov") {
		if (consoleinput.size() >= 9) {
			std::string fov = consoleinput.substr(8, consoleinput.size());
			for (int i = 0; i < fov.size(); i++) {
				if ((fov[i] < '0' || fov[i] > '9') && (fov[i] != ' ' && fov[i] != '.' /*&& fov [i] != ';'*/)) {
					response = "Please enter a valid fov.";
					break;
				}
			}
			if (consoleinput[7] != ' '/* && consoleinput.find(';') == std::string::npos*/) {
				response = "Please enter a valid fov.";
			}
			if (response != "Please enter a valid fov.") {
				float newfov = std::stod(consoleinput.substr(8, consoleinput.size()));
				if (newfov > thecamera->minviewdistance &&  newfov < thecamera->maxviewdistance) {
					thecamera->setFov(std::stod(consoleinput.substr(7, consoleinput.size())));
					response = "New fov is set to " + std::to_string(newfov) + ".";
				}
				else {
					response = "Fov not set since it it exceeds max/min viewdistance.";
				}
			}
		}
		else {
			response = "Please enter a valid fov.";
		}
	}
	else if (consoleinput.substr(0, 19) == "set camera position" && cheatson) {
	if (consoleinput.size() >= 27) {
		int commacount = 0;
		for (int i = 20; i < consoleinput.size(); i++) {
			if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ',' && consoleinput[i] != '-'/* && consoleinput[i] != ';'*/)) {
				response = "Please enter a valid vector3 camera position.";
				break;
			}
			if (consoleinput[i] == ',') {
				commacount++;
			}
		}
		if (commacount != 2) {
			response = "Please enter a valid vector3 camera position.";
		}
		if (consoleinput[19] != ' '/* || consoleinput.find(';') == std::string::npos*/) {
			response = "Please enter a valid vector3 camera position.";
		}
		std::stringstream newinput(consoleinput.substr(20, consoleinput.length()));
		std::string buffer = "";
		std::string newpos = "";
		int count = 0;
		float pos = 0;
		if (response != "Please enter a valid vector3 camera position.") {
			response = "Camera position set to ";
			while (getline(newinput, buffer, ',') && count != 3) {
				pos = std::stod(buffer);
				switch (count) {
				case 0:
					thecamera->cameraposition.x = pos;
					response += std::to_string(pos);
					break;
				case 1:
					thecamera->cameraposition.y = pos;
					response += ", " + std::to_string(pos);
					break;
				case 2:
					thecamera->cameraposition.z = pos;
					response += ", " + std::to_string(pos);
					break;
				}
				count++;
			}
			response += ".";
		}
	}
	else {
		response = "Please enter a valid vector3 camera position.";
	}

	}
	else if (consoleinput.substr(0, 11) == "move camera" && cheatson) {
	if (consoleinput.size() >= 19) {
		int commacount = 0;
		for (int i = 12; i < consoleinput.size(); i++) {
			if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ',' && consoleinput[i] != '-'/* && consoleinput[i] != ';'*/)) {
				response = "Please enter a valid vector3 camera distance.";
				break;
			}

			if (consoleinput[i] == ',') {
				commacount++;
			}
		}
		if (commacount != 2) {
			response = "Please enter a valid vector3 camera distance.";
		}
		if (consoleinput[11] != ' ' /*&& consoleinput.find(';') == std::string::npos*/) {
			response = "Please enter a valid vector3 camera distance.";
		}
		std::stringstream newinput(consoleinput.substr(12, consoleinput.length()));
		std::string buffer = "";
		std::string newpos = "";
		int count = 0;
		float pos = 0;
		if (response != "Please enter a valid vector3 camera distance.") {
			response = "Camera moved up by ";
			while (getline(newinput, buffer, ',') && count != 3) {
				pos = std::stod(buffer);
				switch (count) {
				case 0:
					thecamera->cameraposition.x += pos;
					response += std::to_string(pos);
					break;
				case 1:
					thecamera->cameraposition.y += pos;
					response += ", " + std::to_string(pos);
					break;
				case 2:
					thecamera->cameraposition.z += pos;
					response += ", " + std::to_string(pos);
					break;
				}
				count++;
			}
			response += ".";
		}
	}
	else {
		response = "Please enter a valid vector3 camera distance.";
	}

	}
	else if (consoleinput.substr(0, 16) == "set aspect ratio") {
	if (consoleinput.size() >= 18) {
		for (int i = 16; i < consoleinput.size(); i++) {
			if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ':')) {
				response = "Please enter a valid aspect ratio.";
				break;
			}
		}
		if (consoleinput[16] != ' ') {
			response = "Please enter a valid aspect ratio.";
		}
		std::stringstream newinput(consoleinput.substr(17, consoleinput.length()));
		std::string buffer = "";
		std::string newpos = "";
		int count = 0;
		float pos = 0;
		if (response != "Please enter a valid aspect ratio.") {
			response = "Aspect ratio set to ";
			while (getline(newinput, buffer, ':') && count != 2) {
				pos = std::stod(buffer);
				switch (count) {
				case 0:
					thecamera->aspectratioheight = pos;
					response += std::to_string(pos);
					break;
				case 1:
					thecamera->aspectratiowidth = pos;
					response += ": " + std::to_string(pos);
					break;
				}
				count++;
			}
			response += ".";
		}
	}
	else {
		response = "Please enter a valid aspect ratio.";
	}
	}
	else if (consoleinput == "mouselook on" && cheatson) {
		thecamera->setMouseLook(true);
		response = "Mouselook has been set on.";
	}
	else if (consoleinput == "mouselook off" && cheatson) {
		thecamera->setMouseLook(false);
		response = "Mouselook has been set off.";
	}
	/*else if (consoleinput.substr(0, 20) == "set min viewdistance") {
	if (consoleinput.size() >= 22) {
		std::string maxviewdistance = consoleinput.substr(21, consoleinput.size());
		for (int i = 0; i < fov.size(); i++) {
			if ((fov[i] < '0' || fov[i] > '9') && (fov[i] != ' ' && fov[i] != '.')) {
				response = "Please enter a valid fov.";
				break;
			}
		}
		if (response != "Please enter a valid fov.") {
			float newfov = std::stod(consoleinput.substr(8, consoleinput.size()));
			if (newfov > thecamera->minviewdistance &&  newfov < thecamera->maxviewdistance) {
				thecamera->setFov(std::stod(consoleinput.substr(7, consoleinput.size())));
				response = "New fov is set to " + std::to_string(newfov) + ".";
			}
			else {
				response = "Fov not set since it it exceeds max/min viewdistance.";
			}
		}
	}
	else {
		response = "Please enter a valid fov.";
	}
	}*/

	//scene/rendering
	else if (consoleinput.substr(0, 10) == "set skybox" && cheatson) {
	/*for (int i = 16; i < consoleinput.size(); i++) {
		if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ':')) {
			response = "Please enter a valid aspect ratio.";
			break;
		}
	}*/
		if (consoleinput.size() > 10) {
			if (consoleinput[10] != ' ') {
				response = "Skybox entered is not valid.";
			}
		}
		else {
			response = "Skybox entered is not valid.";
		}
	std::stringstream newinput(consoleinput.substr(11, consoleinput.length()));
	std::string buffer = "";
	std::string right = "";
	std::string left = "";
	std::string top = "";
	std::string bottom = "";
	std::string front = "";
	std::string back = "";
	int count = 0;
	if (response != "Skybox entered is not valid.") {
		while (getline(newinput, buffer, ',') && count != 6) {
			switch (count) {
			case 0:
				if (buffer != "") {
					right = buffer;
				}
				break;
			case 1:
				if (buffer != "") {
					buffer.erase(0, 1);
					left = buffer;
					break;
				}
			case 2:
				if (buffer != "") {
					buffer.erase(0, 1);
					top = buffer;
					break;
				}
			case 3:
				if (buffer != "") {
					buffer.erase(0, 1);
					bottom = buffer;
					break;
				}
			case 4:
				if (buffer != "") {
					buffer.erase(0, 1);
					front = buffer;
					break;
				}
			case 5:
				if (buffer != "") {
					buffer.erase(0, 1);
					back = buffer;
					break;
				}
			}
			count++;
		}
		std::cout << "Skybox is loading, give it a minute. " << std::endl;
		if (_currentscene.setSkybox(right, left, top, bottom, front, back) == -1) {
			response = "Skybox failed to load, returned an error skybox instead.";
		}
		else {
			response = "Skybox loaded.";
		}
	}
	}
	else if (consoleinput.substr(0, 10) == "set entity" && cheatson) {
		if (consoleinput.substr(10, 10) == " position ") {
			if (consoleinput.size() < 29) {  //check if meets minimum size requirements
				response = "Not a valid input for entity position.";
			}
			else {
				std::vector<int> spaces;
				for (int i = 20; i < consoleinput.size(); i++) { //find last instance of space
					if (consoleinput[i] == ' ') {
						spaces.push_back(i);
					}
				}
				if (spaces.size() < 3) {
					response = "Not a valid input for entity position.";
				}
				else {
					spaces.pop_back();
					spaces.pop_back();
					std::string entity = consoleinput.substr(20, (spaces.back()) - 20);
					if (consoleinput.size() < (spaces.back() + 7)) {
						response = "Not a valid input for entity position.";
					}
					for (int i = spaces.back() + 1; i < consoleinput.size(); i++) {
						if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ',' && consoleinput[i] != '-'/* && consoleinput[i] != ';'*/)) {
							response = "Not a valid input for entity position.";
						}
					}
					std::stringstream newinput(consoleinput.substr(spaces.back() + 1, consoleinput.length()));
					std::string buffer = "";
					std::string newpos = "";
					int count = 0;
					float pos = 0;
					Entity *e = _currentscene.findEntity(entity);
					if (e == nullptr) {
						response = "Not a valid input for entity position.";
					}
					if (response != "Not a valid input for entity position." && response != "Entity not found.") {
						response = entity + " position set to ";
						while (getline(newinput, buffer, ',') && count != 3) {
							pos = std::stod(buffer);
							switch (count) {
							case 0:
								e->transform.position.x = pos;
								response += std::to_string(pos);
								break;
							case 1:
								e->transform.position.y = pos;
								response += ", " + std::to_string(pos);
								break;
							case 2:
								e->transform.position.z = pos;
								response += ", " + std::to_string(pos);
								break;
							}
							count++;
						}
						response += ".";
					}
				}
				}
			}
		else {
			response = "Not a valid entity change input.";
		}
		}
	else if (consoleinput.substr(0, 17) == "set ambient light" && cheatson) {
	if (consoleinput.size() >= 25) {
		int commacount = 0;
		for (int i = 18; i < consoleinput.size(); i++) {
			if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ',' && consoleinput[i] != '-'/* && consoleinput[i] != ';'*/)) {
				response = "Please enter a valid vector3 ambient light.";
				break;
			}
				if (consoleinput[i] == ',') {
				commacount++;
				}
		}
		if (commacount != 2) {
			response = "Please enter a valid vector3 ambient light.";
		}
		if (consoleinput[17] != ' '/* || consoleinput.find(';') == std::string::npos*/) {
			response = "Please enter a valid vector3 ambient light.";
		}
		std::stringstream newinput(consoleinput.substr(18, consoleinput.length()));
		std::string buffer = "";
		std::string newpos = "";
		int count = 0;
		float pos = 0;
		if (response != "Please enter a valid vector3 ambient light.") {
			response = "Ambient light set to ";
			while (getline(newinput, buffer, ',') && count != 3) {
				pos = std::stod(buffer);
				switch (count) {
				case 0:
					_currentscene.ambientlight.x = pos;
					response += std::to_string(pos);
					break;
				case 1:
					_currentscene.ambientlight.y = pos;
					response += ", " + std::to_string(pos);
					break;
				case 2:
					_currentscene.ambientlight.z = pos;
					response += ", " + std::to_string(pos);
					break;
				}
				count++;
			}
			response += ".";
		}
	}
	else {
		response = "Please enter a valid vector3 ambient light.";
	}
	}

	//audio
	else if (consoleinput.substr(0, 10) == "set song" && cheatson) {
	// _currentscene->currentsong
	}

	//physics
	else if (consoleinput.substr(0, 6) == "noclip" && cheatson) {
	if (physicsmanager->noclip) {
		physicsmanager->noclip = false;
		response = "Noclip deactivated.";
	}
	else {
		physicsmanager->noclip = true;
		response = "Noclip activated";
	}
	}
	else if (consoleinput.substr(0, 11) == "set gravity" && cheatson) {
		if (consoleinput.size() >= 19) {
			int commacount = 0;
			for (int i = 12; i < consoleinput.size(); i++) {
				if ((consoleinput[i] < '0' || consoleinput[i] > '9') && (consoleinput[i] != ' ' && consoleinput[i] != '.' && consoleinput[i] != ',' && consoleinput[i] != '-'/* && consoleinput[i] != ';'*/)) {
					response = "Please enter a valid vector3 gravity value.";
					break;
				}
				if (consoleinput[i] == ',') {
					commacount++;
				}
			}
			if (commacount != 2) {
				response = "Please enter a valid vector3 ambient light.";
			}
			if (consoleinput[11] != ' '/* || consoleinput.find(';') == std::string::npos*/) {
				response = "Please enter a valid vector3 gravity value.";
			}
			std::stringstream newinput(consoleinput.substr(12, consoleinput.length()));
			std::string buffer = "";
			std::string newpos = "";
			int count = 0;
			float pos = 0;
			if (response != "Please enter a valid vector3 gravity.") {
				Physicsobject gravitysetter;
				response = "Gravity set to ";
				while (getline(newinput, buffer, ',') && count != 3) {
					pos = std::stod(buffer);
					switch (count) {
					case 0:
						gravitysetter.gravity.x = pos;
						response += std::to_string(pos);
						break;
					case 1:
						gravitysetter.gravity.y = pos;
						response += ", " + std::to_string(pos);
						break;
					case 2:
						gravitysetter.gravity.z = pos;
						response += ", " + std::to_string(pos);
						break;
					}
					count++;
				}
				response += ".";
			}
		}
		else {
			response = "Please enter a valid vector3 gravity value.";
		}
	}
	else if (consoleinput.substr(0, 20) == "spawn boundingsphere" && cheatson) {
		if (consoleinput.size() < 22) {
			response = "Error, please enter a sphere name.";
		}
		else if (consoleinput[20] != ' ') {
			response = "Error, please enter a sphere name.";
		}
		else {
			std::string spherename = consoleinput.substr(21, consoleinput.length());
			Boundingsphere bsphere;
			bsphere.radius *= 4;
			bsphere.setPosition(thecamera->cameraposition);
			resourcemanager->addBoundingSphere(spherename, bsphere); //todo: already in resource manager
			colliders.push_back(&(resourcemanager->getBoundingSphere(spherename)));
			response = "Boundingsphere \"" + spherename + "\" has been added to the current position of the camera.";
		}
	}
	else if (consoleinput.substr(0, 30) == "spawn axis-aligned boundingbox" && cheatson) {
	if (consoleinput.size() < 32) {
		response = "Error, please enter an AABB name.";
	}
	else if (consoleinput[30] != ' ') {
		response = "Error, please enter an AABB name.";
	}
	else {
		std::string boxname = consoleinput.substr(14, consoleinput.length());
		Boundingbox aabbox;
		aabbox.setHeight(50);
		aabbox.setLength(50);
		aabbox.setWidth(50);
		aabbox.setPosition(thecamera->cameraposition);
		resourcemanager->addAABB(boxname, aabbox); //todo: already in resource manager
		colliders.push_back(&(resourcemanager->getAABB(boxname)));
		response = "AABB \"" + boxname + "\" has been added to the current position of the camera.";
		}
	}
	else if (consoleinput.substr(0, 10) == "spawn AABB" && cheatson) {
	if (consoleinput.size() < 12) {
		response = "Error, please enter an AABB name.";
	}
	else if (consoleinput[10] != ' ') {
		response = "Error, please enter an AABB name.";
	}
	else {
		std::string boxname = consoleinput.substr(11, consoleinput.length());
		Boundingbox aabbox;
		aabbox.setPosition(thecamera->cameraposition);
		resourcemanager->addAABB(boxname, aabbox); //todo: already in resource manager
		colliders.push_back(&(resourcemanager->getAABB(boxname)));
		response = "AABB \"" + boxname + "\" has been added to the current position of the camera.";
	}
	}
	/*else if (consoleinput.substr(0, 17) == "set physicsobject " && cheatson) {
	if (consoleinput.size() < 22) {
		response = "Error, please enter a sphere name.";
	}
	else if (consoleinput[20] != ' ') {
		response = "Error, please enter a sphere name.";
	}
	else {
		std::string spherename = consoleinput.substr(14, consoleinput.length());
		Boundingsphere bsphere;
		bsphere.setPosition(thecamera->cameraposition);
		resourcemanager.addBoundingSphere(spherename, bsphere); //todo: already in resource manager
		physicsmanager->physicsobjects.push_back(&(resourcemanager.getBoundingSphere(spherename)));
		response = "Boundingsphere \"" + spherename + "\" has been added to the current position of the camera.";
	}
	}*/

	//misc.
	else if (consoleinput == consolecheatspassword) {
		if (cheatson) {
			cheatson = false;
			response = "Cheats off.";
		}
		else {
			cheatson = true;
			response = "Cheats on.";
		}
	}
	else if (consoleinput == "framebyframe" && cheatson) {
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
	else if (consoleinput.substr(0, 14) == "lock framerate" && cheatson) { //todo: adding choice of framerate
		framelock = true;
		deltatime = dtime; 
		response = "Framerate attempted to be locked.";
		/*std::string input = "";
		if (consoleinput.length() >= 16) {
			if (consoleinput.substr(15, consoleinput.size())  )
				
			
			for (int i = 0; i < consoleinput.length(); i++) {
				if (consoleinput[i] >= 48 && consoleinput[i] <= 57) {		//found input
						if (consoleinput[i] < 48 || consoleinput[i] > 57) {
							input = "";
					}
				}
				else if (consoleinput[i] == ' ') {		//skip whitespace
					continue;
				}
				else {				//cancel if character invalid
					input = "";
					break;
				}
			}
		}*/
	
	}
	else if (consoleinput == "unlock framerate" && cheatson) {
	framelock = false;
	response = "Framerate unlocked.";
	}
	else if ((consoleinput.substr(0, 19) == "multiply delta time" || consoleinput.substr(0,19) == "multiply game speed") && cheatson) {
	std::vector<int> delta;
	if (consoleinput.length() >= 21) {
		for (int i = 20; i < consoleinput.length(); i++) {
			if (consoleinput[i] >= '0' && consoleinput[i] <= '9' || consoleinput[i] == ' ') {
				if (consoleinput[i] == ' ') {
					continue;
				}
				else if (consoleinput[i - 1] != ' ') {
					delta.clear();
					break;
				}
				else if (i == consoleinput.length() - 1) {
					delta.push_back(consoleinput[i] - '0');
				}
				else if (consoleinput[i + 1] != ' ') {
					delta.clear();
					break;
				}
				else {
					delta.push_back(consoleinput[i] - '0');
				}
			}
			else {
				delta.clear();
				break;
			}
		}
		if (delta.size() == 1) {
			if (framelock == true) {
				deltatimeweight *= (float)delta[0];
				deltatime *= (float)delta[0];
			}
			if (framelock == false) {
				deltatimeweight *= (float)delta[0];
			}
			response = "Delta multiplied by " + std::to_string(delta[0]) + ".";
		}
		else {
			response = "Error, please enter a number between 0 and 9.";
		}
	}
	else {
		response = "Error, please enter a nunmber between 0 and 9.";
	}
	/*if (consoleinput.length() > 15) {
		for (int i = 15; i < consoleinput.length(); i++) {  //look for decimal
			if (consoleinput[i] == '.') {  //found a decimal
				for (int u = i - 1; u > 14; u--) {  //check left

					if (consoleinput[u] < '0' || consoleinput[u] > '9') {
						if (consoleinput[u] == ' ') {  //skip if valid whitespace
							if (consoleinput[u - 1] != ' ' || consoleinput[u + 1] != ' ' && u != i - 1) {
								response = "Error, please enter a valid number.";
							}
						}
						else {
							response = "Error, please enter a valid number.";
						}
					}
				}

				for (int w = i; w < consoleinput.length(); w++) {  //check right
					if (consoleinput[w] < '0' || consoleinput[w] > '9' && w != i) {
						if (consoleinput[w] == ' ') {	//check whitespace
							if (consoleinput[w - 1] != ' ' && w != i + 1) {
								response = "Error, please enter a valid number.";
							}
							}

							if (w != consoleinput.length() - 1) {
								if consoleinput[w + 1] !=
							}

						}

						else {
							response = "Error, please enter a valid number.";
						}
					}
				}
				if (response != "Error, please enter a valid number.") {  //it's ok
					response = "Delta time has been set to ";
				}
			}
		}
		
		if (response != "Delta time has been set to "){		//look for integer
			for (int i = 15; i < consoleinput.length(); i++) {
				if (consoleinput[i] >= '0' && consoleinput[i] <= '9') {  //found a decimal
					for (int u = i - 1; u > 15; u--) {  //check left
						if (consoleinput[u] < '0' || consoleinput[u] > '9') {
							response = "Error, please enter a valid number.";
						}
					}
					for (int w = i; w < consoleinput.length(); w++) {  //check right
						if (consoleinput[w] < '0' || consoleinput[w] > '9' && consoleinput[w] != ' ' && w != i) {
							response = "Error, please enter a valid number.";
						}
					}
					if (response != "Error, please enter a valid number.") {  //it's ok
						response = "Delta time has been set to ";
					}
				}
		}
		else {
			response = "Error pleaese enter a valid number.";
		}*/
	}
	else if ((consoleinput.substr(0, 17) == "divide delta time" || consoleinput.substr(0, 17) == "divide game speed") && cheatson) {
	std:: vector<int> delta;
	if (consoleinput.length() >= 19) {
	for (int i = 18; i < consoleinput.length(); i++) {
		if (consoleinput[i] >= '1' && consoleinput[i] <= '9' || consoleinput[i] == ' ') {
			if (consoleinput[i] == ' ') {
				continue;
			}
			else if (consoleinput[i - 1] != ' ') {
				delta.clear();
				break;
			}
			else if (i == consoleinput.length() - 1) {
				delta.push_back(consoleinput[i] - '0');
			}
			else if (consoleinput[i + 1] != ' ') {
				delta.clear();
				break;
			}
			else {
				delta.push_back(consoleinput[i] - '0');
			}
		}
		else {
			delta.clear();
			break;
		}
	}
	if (delta.size() == 1) {
		if (framelock == true) {
			deltatimeweight /= (float)delta[0];
			deltatime /= (float)delta[0];
		}
		else if (framelock == false) {
			deltatimeweight /= (float)delta[0];
		}
		response = "Delta divided by " + std::to_string(delta[0]) + ".";
	}
	else {
		response = "Error, please enter a number between 1 and 9.";
	}
}
else {
	response = "Error, please enter a number between 1 and 9.";
}
/*if (consoleinput.length() > 15) {
	for (int i = 15; i < consoleinput.length(); i++) {  //look for decimal
		if (consoleinput[i] == '.') {  //found a decimal
			for (int u = i - 1; u > 14; u--) {  //check left

				if (consoleinput[u] < '0' || consoleinput[u] > '9') {
					if (consoleinput[u] == ' ') {  //skip if valid whitespace
						if (consoleinput[u - 1] != ' ' || consoleinput[u + 1] != ' ' && u != i - 1) {
							response = "Error, please enter a valid number.";
						}
					}
					else {
						response = "Error, please enter a valid number.";
					}
				}
			}

			for (int w = i; w < consoleinput.length(); w++) {  //check right
				if (consoleinput[w] < '0' || consoleinput[w] > '9' && w != i) {
					if (consoleinput[w] == ' ') {	//check whitespace
						if (consoleinput[w - 1] != ' ' && w != i + 1) {
							response = "Error, please enter a valid number.";
						}
						}

						if (w != consoleinput.length() - 1) {
							if consoleinput[w + 1] !=
						}

					}

					else {
						response = "Error, please enter a valid number.";
					}
				}
			}
			if (response != "Error, please enter a valid number.") {  //it's ok
				response = "Delta time has been set to ";
			}
		}
	}

	if (response != "Delta time has been set to "){		//look for integer
		for (int i = 15; i < consoleinput.length(); i++) {
			if (consoleinput[i] >= '0' && consoleinput[i] <= '9') {  //found a decimal
				for (int u = i - 1; u > 15; u--) {  //check left
					if (consoleinput[u] < '0' || consoleinput[u] > '9') {
						response = "Error, please enter a valid number.";
					}
				}
				for (int w = i; w < consoleinput.length(); w++) {  //check right
					if (consoleinput[w] < '0' || consoleinput[w] > '9' && consoleinput[w] != ' ' && w != i) {
						response = "Error, please enter a valid number.";
					}
				}
				if (response != "Error, please enter a valid number.") {  //it's ok
					response = "Delta time has been set to ";
				}
			}
	}
	else {
		response = "Error pleaese enter a valid number.";
	}*/
	}
	else if (consoleinput == "echo console"  && cheatson) {
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
void Console::setPassword(std::string password)
{
	consolecheatspassword = password;
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
