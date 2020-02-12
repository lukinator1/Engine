#include "Messaging.h"
Messagesystem::Messagesystem()
{
}
Messagesystem::~Messagesystem()
{
}
void Messagesystem::messageSystemStartup() {

}
void Messagesystem::messageSystemUpdate(Input &Inputs, Window &window, Camera &camera)  //messages serviced here
{
	if (messagequeue.empty() == false) {
		Message messageoutput = messagequeue.front();
		messageoutput.messagedataone = messageoutput.messagedataone;
		messageoutput.messagedatatwo = messageoutput.messagedatatwo;
		messageDispatch(messageoutput, Inputs, window, camera);
	}
}
void Messagesystem::messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera) {	//messages ordered here, extern
		Inputs.handleMessage(message);
		Window.handleMessage(message);
		/*Camera.handleMessage(message);*/
		messagequeue.pop();
		std::cout << "event: " << static_cast<std::underlying_type<Message::Messagetypes>::type>(message.messagetype) << "handeled" << std::endl;
}




void Messagesystem::messageSystemShutdown()
{

}
void Messagesystem::clearMessageQueue() {
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
