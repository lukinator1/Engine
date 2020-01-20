#pragma once
#include <queue>
#include <string>
#include <queue>
#include "Message.h"
#include "Engine.h"
#include "Input.h"
#include "Window.h"
//the user should define the logic of this class
class Messaging
{
private:
	std::queue <Message> messagequeueprocessor;
public:
	void messagingStartup();
	void messageUpdate(Input &Inputs, Window &Window);
	void messagingShutdown();
	void messageDispatch(Message &message, Input &Inputs, Window &Window);
	void clearMessageQueue();
	Messaging();
	~Messaging();
};

