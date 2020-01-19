#include "Input.h"
//capturemouse
void Input::getInputs(){
	SDL_Event sdlevent;
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
