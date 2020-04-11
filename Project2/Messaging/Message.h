#pragma once
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
		Maximized,
		Minimized,
		Textinput,
		Textcommit,
		Consoleoff,
		Resize,
		User
	};

	enum Category {
		All, 
		Input,
		Window,
		Console,
		User
	};

	Messagetypes messagetype;
	Category messagecategory;
	int messagedataone;
	int messagedatatwo;
	std::string messagedatathree;
	Message(Messagetypes incomingmessagetype, Category incomingmessagecategory);
	~Message();
};


