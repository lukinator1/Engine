#pragma once
#include <string>
class Message {
public:
	enum class Messagetypes {
		Keydown, 
		Keyup, 
		Mousemoved, 
		Mousepressed, 
		Mouseunpressed, 
		Mousewheel,
		Windowclose
		};
	Messagetypes messagetype;
	Message(Messagetypes incomingmessagetype);
	~Message();
};

