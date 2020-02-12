#pragma once
#include <string>
#include "../MathLibrary/vector2.h"
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
	vector2 messagedatathree;
	Message(Messagetypes incomingmessagetype, Category incomingmessagecategory);
	~Message();
};


