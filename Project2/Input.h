#pragma once
#include <SDL2/SDL.h>
#include "Engine.h"
#include <string>
class Input
{
private: 

public:
	enum Keys {
		Esc,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		Delete,
		Tilde, //not actually tilde, the key that has tilde
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Zero,
		Minus,
		Plus,
		Backspace,
		Tab,
		Q, W, E, R, T, Y, U, I, O, P,
		leftbrace, rightbrace, backslash,
		Capslock, A, S, D, F, G, H, J, K, L, 
		semicolon, singlequote, enter,
		leftshift, Z, X, C, V, B, N, M,
		comma, period, forwardslash, rightshift,
		control, windows, leftalt, space, rightalt,
		keyleft, keyup, keydown, keyright
	};
	Input();
	~Input();
	void handleMessage();
	void postMessage(Message message);
	void getInputs();
	bool leftMousePressed();
	bool rightMousePressed();
	bool leftMouseReleased();
	bool rightMouseReleased();
	int* getKeysPressed();
	int* getKeysReleased();
	std::string getKeyname();
	void update();
	bool isKeyPressed();

};

