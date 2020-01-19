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
		Mousewheel,
		Windowclose
		};
	Messagetypes messagetype;
	Message(Messagetypes incomingmessagetype);
	~Message();
};

