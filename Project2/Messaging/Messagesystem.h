#pragma once
#include <queue>
#include <iostream>
#include "Message.h"
#include "../Input.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Global.h"
#include "../Console.h"
class Messagesystem
{
private:
public:
	void messageSystemStartup();
	void messageSystemUpdate(Input &Inputs, Window &Window, Camera &camera, Console &Console);
	void messageSystemShutdown();
	void messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera, Console &Console);
	void clearMessageQueue();
	void printMessageQueue();
	std::queue<Message> getMessageQueue();
	void popMessageQueue();
	bool popMessages(Message *& message);
	Messagesystem();
	~Messagesystem();
};

