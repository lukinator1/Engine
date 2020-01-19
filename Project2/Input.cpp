#include "Input.h"
//todo: capturemouse(maybe), textinput
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

		if (sdlevent.type == SDL_KEYDOWN) {;
			postMessage(Message::Messagetypes::Keydown, SDL_GetScancodeFromKey(sdlevent.key.keysym.sym));
		}

		if (sdlevent.type == SDL_MOUSEMOTION) { //mouse buttons down
			postMessage(Message::Messagetypes::Mousemoved);
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
			keyboardstate[SDL_GetScancodeFromKey(sdlevent.key.keysym.sym)] = 0;
			postMessage(Message::Messagetypes::Keyup);
		}
			
		if (sdlevent.type == SDL_QUIT) {
				postMessage(Message::Messagetypes::Windowclose);
				/*Message message(Windowclose);
				postMessage(Windowclose);*/
				std::cout << "messagequeue size: " << messagequeue.size() << std::endl;
			}
	}
}

void Input::getMousePosition() {  //todo, implement vector2f with math library first
	
}
void Input::updateMousePosition(){}
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
/*bool Input::leftMouseReleased()
{ 
}
bool Input::rightMouseReleased()
{
}*/
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
/*const Uint8* Input::getKeysReleased()
{
}*/
void Input::update()
{
}

void Input::inputShutdown()
{
}

void Input::handleMessage()
{
	if (!messagequeue.empty()) { //handle inputs from event system
		Message message = messagequeue.front();
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Mousemoved:
			updateMousePosition();
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
			keyboardstate[message.messagedata] = 1;
			messagequeue.pop();
			break;
		case Message::Messagetypes::Keyup:
			messagequeue.pop();
			break;
		case Message::Messagetypes::Mousescrolled:
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
void Input::postMessage(Message::Messagetypes messagetype, int data)
{
	if (messagequeue.size() < 32) {
		Message newmessage(messagetype);
		newmessage.messagedata = data;
		messagequeue.push(newmessage);
	}
}
/*void Input::copySDLkeyboardstate(SDL::SDL_Keycode){

}*/