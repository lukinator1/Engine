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
		Closebuttonpressed, 
		User
	};

	enum Category {
		All, 
		Input,
		Window,
		User
	};

	Messagetypes messagetype;
	Category messagecategory;
	int messagedataone;
	int messagedatatwo;
	Message(Messagetypes incomingmessagetype, Category incomingmessagecategory);
	~Message();
};


