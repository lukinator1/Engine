#pragma once
#include <queue>
#include "EntryPoint.h"
class Message
{
private:

public:
	Message();
	~Message();
	void messagerStartup();
	void messagerShutdown();
	void postMessage(Message message);
	void handleMessage(Message msg); 
};

