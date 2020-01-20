#include "Message.h"
//periodic updating


Message::Message(Messagetypes incomingmessagetype, Category incomingmessagecategory)
{
	messagetype = incomingmessagetype;
	messagecategory = incomingmessagecategory;
}


Message::~Message()
{
}
