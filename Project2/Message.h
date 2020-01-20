#pragma once
#include <string>
class Message {
public:
	enum class Messagetypes {
		Keydown,
		Keyup,
		Mousemoved,
		Leftmousepressed,
		Rightmousepressed,
		Leftmouseunpressed,
		Rightmouseunpressed,
		M3pressed,
		M3unpressed,
		Doubleclick,
		Mousescrolled,
		Windowclose
	};
	Messagetypes messagetype;
	int messagedataone;
	int messagedatatwo;
	Message(Messagetypes incomingmessagetype);
	~Message();
};


