#pragma once
#include <queue>
#include <iostream>
#include "Message.h"
#include "../Input.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Global.h"
//the user should define the logic of this class
class Messagesystem
{
private:
public:
	void messageSystemStartup();
	void messageSystemUpdate(Input &Inputs, Window &Window, Camera &camera);
	void messageSystemShutdown();
	void messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera);
	void clearMessageQueue();
	void printMessageQueue();
	std::queue<Message> getMessageQueue();
	void popMessageQueue();
	Messagesystem();
	~Messagesystem();
};

