#include "Messaging.h"
Messaging::Messaging()
{
}
Messaging::~Messaging()
{
}
void Messaging::messagingStartup() {

}
void Messaging::messagingStartup() {

}


void Messaging::messageUpdate(Input &Inputs, Window & window)
{
	Message messageoutput = messagequeue.front();
	messageDispatch(messageoutput, Inputs, window);

}

void Messaging::messageDispatch(Message &message, Input &Inputs, Window &Window)
{
	Inputs.handleMessage();
	Window.handleMessage(message);
	messagequeue.pop();
}




void Messaging::messagingShutdown()
{

}
void Messaging::clearMessageQueue() {
	for (int i = 0; i < messagequeue.size(); i++) {
		messagequeue.pop();
	}
}
void printMessageQueue() {
	std::queue <Message> tempqueue = messagequeue;
	for (int i = 0; i < messagequeue.size(); i++) {
		std::cout << "Current message queue: " << std::endl; 
		std::cout << i << ": " << static_cast<std::underlying_type<Message::Messagetypes>::type>(tempqueue.front().messagetype) << std::endl;
	}
}
