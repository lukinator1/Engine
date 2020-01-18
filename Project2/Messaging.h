#pragma once
#include <queue>
#include <string>
#include "Message.h"
class Messaging
{
private:
	std::queue <Message> messagequeue;
public:
	void postMessage(Message message);
	Messaging();
	~Messaging();
};

