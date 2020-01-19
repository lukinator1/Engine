#pragma once
#include <SDL2/SDL.h>
#include "Engine.h"
#include <string>
#include <iostream>
class Input
{
private:
	bool leftmousepressed;
	bool rightmousepressed;
	bool middlemousepressed;
	bool doubleclicked;				//todo: mouse position

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
		leftbracket = 47,
		rightbracket = 48,
		backslash = 49,
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
		semicolon = 51,
		apostrophe = 52,
		enter = 40,
		leftshift = 225,
		Z = 29,
		X = 27,
		C = 6,
		V = 25,
		B = 5,
		N = 17,
		M = 16,
		comma = 54,
		period = 55,
		forwardslash = 56,
		rightshift = 229,
		control = 224,
		windows = 227,
		leftalt = 226,
		space = 44,
		rightalt = 230,
		keyleft = 80,
		keyup = 82,
		keydown = 81,
		keyright = 79
	};
	Input();
	~Input();
	Uint8 keyboardstate[230] = { 0 };
	const Uint8 *sdlkeyboard = SDL_GetKeyboardState(NULL);

	void inputStartup();
	void inputShutdown();

	void handleMessage();
	void postMessage(Message::Messagetypes messagetype);
	void postMessage(Message::Messagetypes message, int data);

	void getInputs();
	void getMousePosition();
	void updateMousePosition();
	bool leftMousePressed();
	bool rightMousePressed();
	bool middleMousePressed();
	const Uint8* getKeysPressed();
	/*bool leftMouseReleased();
	bool rightMouseReleased();*/
	/*int* getKeysReleased();*/
	void update();
	bool isKeyPressed(Keys key);

};
