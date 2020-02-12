#pragma once
#include <queue>
#include <string>
#include <iostream>
#include "Message.h"
#include "../Input.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Global.h"
//the user should define the logic of this class
//take off +100
class Messagesystem
{
private:
public:
	void messageSystemStartup();
	void messageSystemUpdate(Input &Inputs, Window &Window, Camera &camera);
	void messageSystemShutdown();
	void messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera);
	void clearMessageQueue();
	Messagesystem();
	~Messagesystem();
};

