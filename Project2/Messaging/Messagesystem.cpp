#include "Messaging.h"
/*void Messagesystem::messageSystemStartup() {

}*/
void Messagesystem::messageSystemUpdate(Input &Inputs, Window &window, Camera &camera, Console &Console)  //messages serviced here
{
	while (messagequeue.empty() == false) {
		Message messageoutput = messagequeue.front();
		messageoutput.messagedataone = messageoutput.messagedataone;
		messageoutput.messagedatatwo = messageoutput.messagedatatwo;
		messageDispatch(messageoutput, Inputs, window, camera, Console);
	}
}
void Messagesystem::messageDispatch(Message &message, Input &Inputs, Window &Window, Camera &Camera, Console &Console) {	//messages ordered here, extern
		/*nputs.handleMessage(message);*/
		Window.handleMessage(message);
		Console.handleMessage(message);
		/*Camera.handleMessage(message);*/
		messagequeue.pop();
		/*std::cout << "event: " << static_cast<std::underlying_type<Message::Messagetypes>::type>(message.messagetype) << "handeled" << std::endl;*/
}
void Messagesystem::clearMessageQueue() {
	for (int i = 0; i < messagequeue.size(); i++) {
		messagequeue.pop();
	}
}
void Messagesystem::printMessageQueue() {
	std::queue <Message> tempqueue = messagequeue;
	for (int i = 0; i < tempqueue.size(); i++) {
		std::cout << "Current message queue: " << std::endl; 
		std::cout << i << ": " << static_cast<std::underlying_type<Message::Messagetypes>::type>(tempqueue.front().messagetype) << std::endl;
		tempqueue.pop();
	}
}
std::queue<Message> Messagesystem::getMessageQueue() {
	return messagequeue;
}
void Messagesystem::popMessageQueue() {
	messagequeue.pop();
}
bool Messagesystem::popMessages(Message * &message){
	if (messagequeue.empty() == false) {
		*message = messagequeue.front();
		return true;
	}
	else {
		return false;
	}
}
void Messagesystem::messageSystemShutdown()
{
	clearMessageQueue();
}

Messagesystem::Messagesystem()
{
}
Messagesystem::~Messagesystem()
{
}
