#include "Input.h"
Input::Input()
{
}
Input::~Input()
{
}
void Input::inputStartup()
{
	scrolldistance.setVector(0.0, 0.0);
	mouseposition.setVector(0.0, 0.0);
}
void Input::getInputs() {
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

		if (sdlevent.type == SDL_KEYDOWN && sdlevent.key.repeat == 0) {
			;
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
			postMessage(Message::Messagetypes::Closebuttonpressed);
			/*Message message(Windowclose);
			postMessage(Windowclose);*/
			std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
		}
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
	scrolled = false;
	if (!messagequeue.empty()) { //handle inputs from event system
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Mousemoved:
			updateMousePosition(message.messagedataone, message.messagedatatwo);
			std::cout << "x mouse position: " << mouseposition.x << ", y mouse position: " << mouseposition.y << std::endl;
			break;
		case Message::Messagetypes::Leftmousepressed:
			leftmousepressed = true;
			break;
		case Message::Messagetypes::Rightmousepressed:
			rightmousepressed = true;
			break;
		case Message::Messagetypes::Doubleclick:
			doubleclicked = true;
			break;
		case Message::Messagetypes::M3pressed:
			middlemousepressed = true;
			break;
		case Message::Messagetypes::Leftmouseunpressed:
			leftmousepressed = false;
			break;
		case Message::Messagetypes::Rightmouseunpressed:
			rightmousepressed = false;
			break;
		case Message::Messagetypes::M3unpressed:
			leftmousepressed = false;
			break;
		case Message::Messagetypes::Keydown:
			keyboardstate[message.messagedataone] = 1;
			std::cout << "Key: " << message.messagedataone << std::endl;
			break;
		case Message::Messagetypes::Keyup:
			keyboardstate[message.messagedataone] = 0;
			break;
		case Message::Messagetypes::Mousescrolled:
			setScrolldistance(message.messagedataone, message.messagedatatwo);
			std::cout << "x scroll distance: " << scrolldistance.x << ", y scroll distance: " << scrolldistance.y << std::endl;
			scrolled = true;
			break;
		}
	}
	if (scrolled == false) {
		setScrolldistance(0.0f, 0.0f);
	}
}
void Input::postMessage(Message::Messagetypes messagetype)
{

	if (messagequeue.size() < 32) {
		Message newmessage(messagetype, Message::Category::Input);
		messagequeue.push(newmessage);
	}
}
void Input::postMessage(Message::Messagetypes messagetype, int dataone, int datatwo)
{
	if (messagequeue.size() < 32) {
		Message newmessage(messagetype, Message::Category::Input);
		newmessage.messagedataone = dataone;
		newmessage.messagedatatwo = datatwo;
		messagequeue.push(newmessage);
	}
}
