#include "Input.h"
//capturemouse
void Input::getInputs() {
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {

		if (sdlevent.type == SDL_MOUSEBUTTONDOWN) { //mouse buttons down
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
					/*leftmousepressed = true;*/
				if (sdlevent.button.clicks == 2) {
					Message::Messagetypes::Doubleclick;
					postMessage(Message::Messagetypes::Rightmousepressed);
				}
				else{
				Message::Messagetypes::Leftmousepressed;
				postMessage(Message::Messagetypes::Leftmousepressed);
				}
			}
			if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				/*rightmousepressed = true;*/
				Message::Messagetypes::Rightmousepressed;
				postMessage(Message::Messagetypes::Rightmousepressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				/*middlemousepressed = true;*/
				Message::Messagetypes::M3pressed;
				postMessage(Message::Messagetypes::M3pressed);
			}
		}
		
		if (sdlevent.type == SDL_MOUSEBUTTONUP) { //mouse buttons up
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
				/*leftmousepressed = false;*/
					Message::Messagetypes::Leftmouseunpressed;
					postMessage(Message::Messagetypes::Leftmouseunpressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				/*rightmousepressed = false;*/
				Message::Messagetypes::Rightmouseunpressed;
				postMessage(Message::Messagetypes::Rightmouseunpressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				/*middlemousepressed = false;*/
				Message::Messagetypes::M3unpressed;
				postMessage(Message::Messagetypes::M3unpressed);
			}
		}

		if (sdlevent.type == SDL_MOUSEMOTION) { //mouse buttons down
			Message::Messagetypes::Mousemoved;
			postMessage(Message::Messagetypes::Mousemoved);
		}

		if (sdlevent.type == SDL_KEYDOWN) {
			Message::Messagetypes::Keydown;
			postMessage(Message::Messagetypes::Keydown);
		}

		if (sdlevent.type == SDL_KEYUP) {
			Message::Messagetypes::Keyup;
			postMessage(Message::Messagetypes::Keyup);
		}


	}
}

void::getMousePosition() {  //todo, implement vector2f with math library first
	
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
	return middleMousePressed;
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

Input::Input()
{	
}
Input::~Input()
{
}

void Input::inputStartup()
{
	keyboardstate = SDL_GetKeyboardState(NULL);
}
void Input::inputShutdown()
{
}

void Input::handleMessage()
{
	if (!messagequeue.empty()) {
		Message message = messagequeue.front();
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Leftmousepressed:
			leftmousepressed = true;
			messagequeue.pop();
		case Message::Messagetypes::Rightmousepressed:
			rightmousepressed = true;
			messagequeue.pop();
		case Message::Messagetypes::M3pressed:
			middlemousepressed = true;
			messagequeue.pop();
		case Message::Messagetypes::Leftmouseunpressed:
			leftmousepressed = false;
			messagequeue.pop();
		case Message::Messagetypes::Rightmouseunpressed:
			rightmousepressed = false;
			messagequeue.pop();
		case Message::Messagetypes::M3unpressed:
			leftmousepressed = false;
			messagequeue.pop();
		}
	}
}                     

void Input::postMessage(Message message)
{
		messagequeue.push(message);
}
