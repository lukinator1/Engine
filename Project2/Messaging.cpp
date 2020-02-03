#include "Messaging.h"
Messaging::Messaging()
{
}
Messaging::~Messaging()
{
}
void Messaging::messagingStartup() {

}
void Messaging::messageUpdate(Input &Inputs, Window &window, Camera &camera)  //messages serviced here
{
	if (messagequeue.empty() == false) {
		Message messageoutput = messagequeue.front();
		messageoutput.messagedataone = messageoutput.messagedataone;
		messageoutput.messagedatatwo = messageoutput.messagedatatwo;
		messageDispatch(messageoutput, Inputs, window, camera);
	}
}
void Messaging::messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera) {	//messages ordered here, extern
		Inputs.handleMessage(message);
		Window.handleMessage(message);
		Camera.handleMessage(message);
		messagequeue.pop();
		std::cout << "event: " << static_cast<std::underlying_type<Message::Messagetypes>::type>(message.messagetype) << "handeled" << std::endl;
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
