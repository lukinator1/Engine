#include "Input.h"
Input::Input()
{
}
Input::~Input()
{
}
void Input::inputStartup()
{
	/*keyboardstate = SDL_GetKeyboardState(NULL);*/
}
void Input::getInputs() {
	int xscrolldistance = 0;
	int yscrolldistance = 0;
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {

		if (sdlevent.type == SDL_MOUSEBUTTONDOWN) { //mouse buttons down
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
				if (sdlevent.button.clicks == 2) {
					postMessage(Message::Messagetypes::Doubleclick);
				}
				else {
					postMessage(Message::Messagetypes::Leftmousepressed);
				}
			}
			if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				postMessage(Message::Messagetypes::Rightmousepressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				postMessage(Message::Messagetypes::M3pressed);
			}
		}

		if (sdlevent.type == SDL_KEYDOWN && sdlevent.key.repeat == 0) {;
			postMessage(Message::Messagetypes::Keydown, SDL_GetScancodeFromKey(sdlevent.key.keysym.sym), 0);
		}

		if (sdlevent.type == SDL_MOUSEMOTION) { //mouse buttons down
			postMessage(Message::Messagetypes::Mousemoved, sdlevent.motion.x, sdlevent.motion.y);
		}

		if (sdlevent.type == SDL_MOUSEBUTTONUP) { //mouse buttons up
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
					postMessage(Message::Messagetypes::Leftmouseunpressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				postMessage(Message::Messagetypes::Rightmouseunpressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				postMessage(Message::Messagetypes::M3unpressed);
			}
		}

		if (sdlevent.type == SDL_KEYUP) {
			postMessage(Message::Messagetypes::Keyup, SDL_GetScancodeFromKey(sdlevent.key.keysym.sym), 0);
		}

		if (sdlevent.type == SDL_MOUSEWHEEL) {
			postMessage(Message::Messagetypes::Mousescrolled, sdlevent.wheel.x, sdlevent.wheel.y);
		}
			
		if (sdlevent.type == SDL_QUIT) {
				postMessage(Message::Messagetypes::Windowclose);
				/*Message message(Windowclose);
				postMessage(Windowclose);*/
				std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
			}
	}
}

void Input::getMousePosition() {  //todo
	
}
void Input::updateMousePosition(int x, int y){
	xmouseposition = x;
	ymouseposition = y;
}

void Input::getScrolldistance()
{
} //todo
void Input::setScrolldistance(int scrollvertical, int scrollhorizontal) {
	verticalscrolldistance = scrollvertical;
	horizontalscrolldistance = scrollhorizontal;
}

bool Input::leftMousePressed()
{
	return leftmousepressed;
}
bool Input::rightMousePressed()
{
	return rightmousepressed;
}
bool Input::middleMousePressed() {
	return middlemousepressed;
}

const Uint8* Input::getKeysPressed()
{
	return keyboardstate;
}
bool Input::isKeyPressed(Keys key)
{
	if (keyboardstate[key]) {
		return true;
	}
}

void Input::update()
{
}

void Input::inputShutdown()
{
}
void Input::handleMessage(Message &message)
{
	if (!messagequeue.empty()) { //handle inputs from event system
		Message message = messagequeue.front();
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Mousemoved:
			updateMousePosition(message.messagedataone, message.messagedatatwo);
			std::cout << "x mouse position: " << message.messagedataone << ", y mouse position: " << message.messagedatatwo << std::endl;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Leftmousepressed:
			leftmousepressed = true;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Rightmousepressed:
			rightmousepressed = true;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Doubleclick:
			doubleclicked = true;
			messagequeue.pop();
			break;
		case Message::Messagetypes::M3pressed:
			middlemousepressed = true;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Leftmouseunpressed:
			leftmousepressed = false;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Rightmouseunpressed:
			rightmousepressed = false;
			messagequeue.pop();
			break;
		case Message::Messagetypes::M3unpressed:
			leftmousepressed = false;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Keydown:
			keyboardstate[message.messagedataone] = 1;
			std::cout << "Key: " << message.messagedataone << std::endl;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Keyup:
			keyboardstate[message.messagedataone] = 0;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Mousescrolled:
			setScrolldistance(message.messagedataone, message.messagedatatwo);
			std::cout << "x scroll distance: " << message.messagedataone << ", y scroll distance: " << message.messagedatatwo << std::endl;
			messagequeue.pop();
			break;
		}
		std::cout << "event: " << static_cast<std::underlying_type<Message::Messagetypes>::type>(message.messagetype) << "handeled" << std::endl;
	}
}      
void Input::postMessage(Message::Messagetypes messagetype)
{
	if (messagequeue.size() < 32) {
		Message newmessage(messagetype);
		messagequeue.push(newmessage);
	}
}
void Input::postMessage(Message::Messagetypes messagetype, int dataone, int datatwo)
{
	if (messagequeue.size() < 32) {
		Message newmessage(messagetype);
		newmessage.messagedataone = dataone;
		newmessage.messagedatatwo = datatwo;
		messagequeue.push(newmessage);
	}
}