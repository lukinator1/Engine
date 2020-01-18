#pragma once
#include <queue>
#include <string>
#include "Message.h"
class Messaging
{
private:
public:
	void postMessage(Message message);
	Messaging();
	~Messaging();
};

