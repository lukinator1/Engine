#include "Messaging.h"



void Messaging::postMessage(Message message)
{
	messagequeue.push(message);
}
Messaging::Messaging()
{
}


Messaging::~Messaging()
{
}
