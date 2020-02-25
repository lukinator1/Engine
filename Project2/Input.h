#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "Messaging/Message.h"
#include "Mathlibrary/vector2.h"
#include "Global.h"
//todo: capturemouse(maybe), textinput, custom cursor, keyheld
class Input
{
private:
	SDL_Event sdlevent;
	/*bool leftmousepressed;
	bool rightmousepressed;
	bool middlemousepressed;
	bool doubleclicked;
	vector2 previousmouseposition;
	vector2 mouseposition;
	vector2 mousemovementdistance;
	vector2 scrolldistance;*/

public:
	enum Keys {
		Esc = 41,
		F1 = 58,
		F2 = 59,
		F3 = 60,
		F4 = 61,
		F5 = 62,
		F6 = 63,
		F7 = 64,
		F8 = 65,
		F9 = 66,
		F10 = 67,
		F11 = 68,
		F12 = 69,
		Delete = 76,
		Grave = 53,
		One = 30,
		Two = 31,
		Three = 32,
		Four = 33,
		Five = 34,
		Six = 35,
		Seven = 36,
		Eight = 37,
		Nine = 38,
		Zero = 39,
		Minus = 45,
		Equal = 46,
		Backspace = 42,
		Tab = 43,
		Q = 20,
		W = 26,
		E = 8,
		R = 21,
		T = 23,
		Y = 28,
		U = 24,
		I = 12,
		O = 18,
		P = 19,
		Leftbracket = 47,
		Rightbracket = 48,
		Backslash = 49,
		Capslock = 57,
		A = 4,
		S = 22,
		D = 7,
		F = 9,
		G = 10,
		H = 11,
		J = 13,
		K = 14,
		L = 15,
		Semicolon = 51,
		Apostrophe = 52,
		Enter = 40,
		Leftshift = 225,
		Z = 29,
		X = 27,
		C = 6,
		V = 25,
		B = 5,
		N = 17,
		M = 16,
		Comma = 54,
		Period = 55,
		Forwardslash = 56,
		Rightshift = 229,
		Control = 224,
		Windows = 227,
		Leftalt = 226,
		Space = 44,
		Rightalt = 230,
		Keyleft = 80,
		Keyup = 82,
		Keydown = 81,
		Keyright = 79

	};
	Input();
	~Input();
	std::pair<bool, bool> keyboardstate[230] = {  };
	std::pair<bool, bool> leftmouse;
	std::pair<bool, bool> rightmouse;
	std::pair<bool, bool> middlemouse;
	bool doubleclicked;
	/*Mouse Mouse;*/
	vector2 previousmouseposition;
	vector2 mouseposition;
	vector2 mousemovementdistance;
	vector2 scrolldistance;
	bool moved;
	bool scrolled;

	const Uint8 *sdlkeyboard = SDL_GetKeyboardState(NULL);

	void inputStartup();
	void inputShutdown();

	void handleMessage(Message &message);
	void postMessage(Message::Messagetypes messagetype);
	void postMessage(Message::Messagetypes message, int dataone, int data);

	void postMessage(Message::Messagetypes messagetype, int dataone, int datatwo, std::string datathree);

	void getInputs();
	void hideCursor(bool curse);
	vector2 getMousePosition();
	float getxMousePosition();
	float getyMousePosition();
	void setMousePosition(int x, int y);
	void updateMousePosition(float newx, float newy);
	void updateMousePosition(vector2 newmouseposition);
	vector2 getScrolldistance();
	void setScrolldistance(float scrollvertical, float scrollhorizontal);
	void setScrolldistance(vector2 newscrolldistance);
	void setMouseMovementDistance(float newx, float newy);
	void setMouseMovementDistance(vector2 newmovementdistance);
	vector2 getMouseMovementDistance();
	float getXMouseMovementDistance();
	float getYMouseMovementDistance();
	/*bool leftMousePressed();
	bool rightMousePressed();
	bool middleMousePressed();*/
	std::pair<bool, bool>* getKeysPressed();
	std::pair<bool, bool> getLeftMouse();
	std::pair<bool, bool> getRightMouse();
	std::pair<bool, bool> getMiddleMouse();
	void update();
	/*bool isKeyPressed(Keys key);*/
};