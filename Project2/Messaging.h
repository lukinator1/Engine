#pragma once
#include <queue>
#include <string>
#include <queue>
#include "Message.h"
#include "Engine.h"
#include "Input.h"
#include "Window.h"
#include "Camera.h"
//the user should define the logic of this class
//take off +100
class Messaging
{
private:
public:
	void messagingStartup();
	void messageUpdate(Input &Inputs, Window &Window, Camera &camera);
	void messagingShutdown();
	void messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera);
	void clearMessageQueue();
	Messaging();
	~Messaging();
};

