#include "Input.h"
Input::Input()
{
}
Input::~Input()
{
}
void Input::inputStartup()
{
	scrolldistance.setVector(0.0f, 0.0f); //maybe make this current position?
	mouseposition.setVector(0.0f, 0.0f);
	mousemovementdistance.setVector(0.0f, 0.0f);
}
void Input::getInputs() {  
	scrolled = false;
	moved = false;
	for (int i = 0; i < 230; i++) { //these 2 loops can be manually entered to increase performance (slightly)
		if (keyboardstate[i].first == true) {
			keyboardstate[i].second = true;
		}
	}
	for (int i = 0; i < 230; i++) { 
		keyboardstate[i].first = sdlkeyboard[i];
		if (keyboardstate[i].first == true && keyboardstate[i].second == false) {
			std::cout << "Key: " << i << " pressed" << std::endl;
		}
	}
	if (leftmouse.first == true) {
		leftmouse.second = true;
	}
	leftmouse.first = false;
	if (rightmouse.first == true) {
		rightmouse.second = true;
	}
	rightmouse.first = false;
	if (middlemouse.first == true) {
		middlemouse.second = true;
	}
	middlemouse.first = false;
	doubleclicked = false;
	while (SDL_PollEvent(&sdlevent)) {
		/*if (sdlevent.type == SDL_JOYBUTTONDOWN) {

		}*/
		

		if (sdlevent.type == SDL_MOUSEBUTTONDOWN) { //mouse buttons down
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
				leftmouse.first = true;
				std::cout << "LM clcicked" << std::endl;
				if (sdlevent.button.clicks == 2) {
					/*postMessage(Message::Messagetypes::Doubleclick);*/
					doubleclicked = true;
					std::cout << "Doubleclicked" << std::endl;
				}
				/*else {
					postMessage(Message::Messagetypes::Leftmousepressed);
					
				}*/
			}
			if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				/*postMessage(Message::Messagetypes::Rightmousepressed);*/
				std::cout << "RM clicked" << std::endl;
				rightmouse.first = true;
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				std::cout << "M3 clicked" << std::endl;
				middlemouse.first = true;
				/*postMessage(Message::Messagetypes::M3pressed);*/
			}
		}

		/*if (sdlevent.type == SDL_KEYDOWN) {
			/*postMessage(Message::Messagetypes::Keydown, SDL_GetScancodeFromKey(sdlevent.key.keysym.sym), 0);
			keyboardstate[SDL_GetScancodeFromKey(sdlevent.key.keysym.sym)].first = true;
			/*if (sdlevent.key.repeat == 1) {
				keyboardstate[SDL_GetScancodeFromKey(sdlevent.key.keysym.sym)].second = true;
				std::cout << "Key: " << SDL_GetScancodeFromKey(sdlevent.key.keysym.sym) << " being held" << std::endl;
			}
			else {*/
				/*keyboardstate[SDL_GetScancodeFromKey(sdlevent.key.keysym.sym)].second = false;
			}
			std::cout << "Key: " << SDL_GetScancodeFromKey(sdlevent.key.keysym.sym) << "pressed" << std::endl;
		}*/

		if (sdlevent.type == SDL_MOUSEMOTION) { //mouse buttons down;
			/*postMessage(Message::Messagetypes::Mousemoved, sdlevent.motion.x, sdlevent.motion.y, sdlevent.motion.xrel, -sdlevent.motion.yrel);*/
			mousemovementdistance.x = sdlevent.motion.xrel;
			mousemovementdistance.y = -sdlevent.motion.yrel;
			moved = true;
		}

		if (sdlevent.type == SDL_MOUSEBUTTONUP) { //mouse buttons up
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
				/*postMessage(Message::Messagetypes::Leftmouseunpressed);*/
				leftmouse.first = false;
				leftmouse.second = false;
			}
			else if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				/*postMessage(Message::Messagetypes::Rightmouseunpressed);*/
				rightmouse.first = false;
				rightmouse.second = false;
			}
			else if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				/*postMessage(Message::Messagetypes::M3unpressed);*/
				middlemouse.first = false;
				middlemouse.second = false;
			}
		}

		if (sdlevent.type == SDL_KEYUP) {
			/*postMessage(Message::Messagetypes::Keyup, SDL_GetScancodeFromKey(sdlevent.key.keysym.sym), 0);*/
			keyboardstate[SDL_GetScancodeFromKey(sdlevent.key.keysym.sym)].first = false;
			keyboardstate[SDL_GetScancodeFromKey(sdlevent.key.keysym.sym)].second = false;
		}

		if (sdlevent.type == SDL_MOUSEWHEEL) {
			/*postMessage(Message::Messagetypes::Mousescrolled, sdlevent.wheel.x, sdlevent.wheel.y);
			scrolled = true;*/
			setScrolldistance(sdlevent.wheel.x, sdlevent.wheel.y);
			std::cout << "x scroll distance: " << scrolldistance.x << ", y scroll distance: " << scrolldistance.y << std::endl;
			scrolled = true;
		}

		if (sdlevent.type == SDL_TEXTEDITING) {
			postMessage(Message::Messagetypes::Textinput, 0, 0, sdlevent.edit.text);
			std::cout << "text input event" << std::endl;
		}
		if (sdlevent.type == SDL_TEXTINPUT) {
			postMessage(Message::Messagetypes::Textcommit, 0, 0, sdlevent.text.text);
			std::cout << "text commit event" << std::endl;
		}
	
		if (sdlevent.type == SDL_WINDOWEVENT) {
			if (sdlevent.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
				postMessage(Message::Messagetypes::Maximized);
			}
			else if (sdlevent.window.event == SDL_WINDOWEVENT_MINIMIZED) {
				postMessage(Message::Messagetypes::Minimized);
			}
		}

		if (sdlevent.type == SDL_QUIT) {
			postMessage(Message::Messagetypes::Closebuttonpressed);
			/*Message message(Windowclose);
			postMessage(Windowclose);*/
			std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
		}
	}
	if (scrolled == false) {
		setScrolldistance(0.0f, 0.0f);
	}
	if (moved == false) {
		setMouseMovementDistance(0.0f, 0.0f);
	}
}
void Input::hideCursor(bool curse) {
	if (curse == true) {
		SDL_ShowCursor(SDL_DISABLE);
	}
	else  {
		SDL_ShowCursor(SDL_ENABLE);
	}
}
vector2 Input::getMousePosition() {  //todo
	return mouseposition;
}
float Input::getxMousePosition()
{
	return mouseposition.x;
}
float Input::getyMousePosition()
{
	return mouseposition.y;
}
void Input::setMousePosition(int x, int y) { //could be an error here
	SDL_WarpMouseInWindow(nullptr, x, y);
	mouseposition.x = x;
	mouseposition.y = y;
}
void Input::updateMousePosition(float newx, float newy)
{
	mouseposition.x = newx;
	mouseposition.y = newy;
}
void Input::updateMousePosition(vector2 newmouseposition) {
	mouseposition = newmouseposition;
}
vector2 Input::getScrolldistance()
{
	return scrolldistance;
}
void Input::setScrolldistance(float newx, float newy) {
	scrolldistance.x = newx;
	scrolldistance.y = newy;
}
void Input::setScrolldistance(vector2 newscrolldistance) {
	scrolldistance = newscrolldistance;
}
void Input::setMouseMovementDistance(float newx, float newy) {
	mousemovementdistance.x = newx;
	mousemovementdistance.y = newy;
}
void Input::setMouseMovementDistance(vector2 newmovementdistance) {
	mousemovementdistance = newmovementdistance;
}
vector2 Input::getMouseMovementDistance() {
	return mousemovementdistance;
}
float Input::getXMouseMovementDistance() {
	return mousemovementdistance.x;
}
float Input::getYMouseMovementDistance() {
	return mousemovementdistance.y;
}
/*bool Input::leftMousePressed()
{
	return leftmousepressed;
}
bool Input::rightMousePressed()
{
	return rightmousepressed;
}
bool Input::middleMousePressed() {
	return middlemousepressed;
}*/
std::pair<bool, bool>* Input::getKeysPressed()
{
	return keyboardstate;
}
std::pair<bool, bool> Input::getLeftMouse() {
	return leftmouse;
}
std::pair<bool, bool> Input::getRightMouse() {
	return rightmouse;
}
std::pair<bool, bool> Input::getMiddleMouse() {
	return middlemouse;
}
/*bool Input::isKeyPressed(Keys key)
{
	if (keyboardstate[key].first) {
		return true;
	}
}*/
void Input::update()
{
}
void Input::inputShutdown()
{
}
void Input::handleMessage(Message &message)
{
	/*Mouse.scrolled = false;
	Mouse.moved = false;*/
	if (!messagequeue.empty()) { //handle inputs from event system
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Mousemoved:
			/*setMouseMovementDistance(message.messagedatathree);*/
			/*updateMousePosition(message.messagedataone, message.messagedatatwo);
			std::cout << "x mouse position/distance : " << mouseposition.x << ", " << getXMouseMovementDistance() << " , y mouse position/distance: " << mouseposition.y << ", " << getYMouseMovementDistance() << std::endl;
			moved = true;*/
			break;
		case Message::Messagetypes::Leftmousepressed:
			/*Mouse.leftmousepressed = true;*/
			break;
		case Message::Messagetypes::Rightmousepressed:
			/*Mouse.rightmousepressed = true;*/
			break;
		case Message::Messagetypes::Doubleclick:
			/*doubleclicked = true;*/
			break;
		case Message::Messagetypes::M3pressed:
			/*Mouse.middlemousepressed = true;*/
			break;
		case Message::Messagetypes::Leftmouseunpressed:
			/*leftmousepressed = false;
			break;*/
		case Message::Messagetypes::Rightmouseunpressed:
			/*rightmousepressed = false;
			break;*/
		case Message::Messagetypes::M3unpressed:
			/*leftmousepressed = false;
			break;*/
		case Message::Messagetypes::Keydown:
			/*keyboardstate[message.messagedataone].first = true; 
			keyboardstate[message.messagedataone].second = message.messagedatatwo;
			std::cout << "Key: " << message.messagedataone << std::endl;*/
			break;
		case Message::Messagetypes::Keyup:
			/*keyboardstate[message.messagedataone].first = true;
			keyboardstate[message.messagedataone].second = message.messagedatatwo;*/
			break;
		case Message::Messagetypes::Mousescrolled:
			/*setScrolldistance(message.messagedataone, message.messagedatatwo);
			std::cout << "x scroll distance: " << scrolldistance.x << ", y scroll distance: " << scrolldistance.y << std::endl;
			scrolled = true;*/
			break;
		}
	}
	/*if (scrolled == false) {
		setScrolldistance(0.0f, 0.0f);
	}
	if (moved == false) {
		setMouseMovementDistance(0.0f, 0.0f);
	}*/
}
void Input::postMessage(Message::Messagetypes messagetype)
{

	if (messagequeue.size() < messagequeuecapacity) {
		Message newmessage(messagetype, Message::Category::Input);
		messagequeue.push(newmessage);
	}
}
void Input::postMessage(Message::Messagetypes messagetype, int dataone, int datatwo)
{
	if (messagequeue.size() < messagequeuecapacity) {
		Message newmessage(messagetype, Message::Category::Input);
		newmessage.messagedataone = dataone;
		newmessage.messagedatatwo = datatwo;
		messagequeue.push(newmessage);
	}
}
void Input::postMessage(Message::Messagetypes messagetype, int dataone, int datatwo, std::string datathree)
{
	if (messagequeue.size() < messagequeuecapacity) {
		Message newmessage(messagetype, Message::Category::Input);
		newmessage.messagedataone = dataone;
		newmessage.messagedatatwo = datatwo;
		newmessage.messagedatathree = datathree;
		/*newmessage.messagedatathree.y = datathreey;*/
		messagequeue.push(newmessage);
	}
}

