#include "Input.h"
//capturemouse
void Input::getInputs() {
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {

		if (sdlevent.type == SDL_MOUSEBUTTONDOWN) { //mouse buttons down
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
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
				Message::Messagetypes::Rightmousepressed;
				postMessage(Message::Messagetypes::Rightmousepressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				Message::Messagetypes::M3pressed;
				postMessage(Message::Messagetypes::M3pressed);
			}
		}
		
		if (sdlevent.type == SDL_MOUSEBUTTONUP) { //mouse buttons up
			if (sdlevent.button.button == SDL_BUTTON_LEFT) {
					Message::Messagetypes::Leftmouseunpressed;
					postMessage(Message::Messagetypes::Leftmouseunpressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
				Message::Messagetypes::Rightmouseunpressed;
				postMessage(Message::Messagetypes::Rightmouseunpressed);
			}
			if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
				Message::Messagetypes::M3unpressed;
				postMessage(Message::Messagetypes::M3unpressed);
			}
		}

		if (sdlevent.type == SDL_MOUSEMOTION) { //mouse buttons down
			Message::Messagetypes::Mousemoved;
			postMessage(Message::Messagetypes::Mousemoved);
		}



	}
}
void::getMousePosition() {
	
}
bool Input::leftMousePressed()
{
	SDL_Event sdlevent;
	if
}
bool Input::rightMousePressed()
{
}

bool Input::leftMouseReleased()
{
}

bool Input::rightMouseReleased()
{
}

int* Input::getKeysPressed()
{
}

int* Input::getKeysReleased()
{
}

std::string Input::getKeyname()
{
}

void Input::update()
{
}

bool Input::isKeyPressed()
{
	
}

Input::Input()
{
	
}
Input::~Input()
{
}

void Input::handleMessage()
{
	if (!messagequeue.empty()) {
		Message message = messagequeue.front();
		switch (message.messagetype) { //other window functions
		case Message::Messagetypes::Windowclose:
			messagequeue.pop();
			break;
		}
	}
}                     

void Input::postMessage(Message message)
{
		messagequeue.push(message);
}
