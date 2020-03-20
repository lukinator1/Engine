#pragma once
#include "../Rendering/Transforming.h"
#include "../Rendering/Shader.h"
#include "../Global.h"
class Component{
public:  //deltas passed in here
	virtual void updateComponent(Transforming &t) {

	}
	virtual void componentInput(Transforming &t) {

	}
	virtual void renderComponent(Transforming &t, Shader * &s) {

	}
	virtual void initializeComponent() {

	}
	/*virtual void renderComponent() {

	}*/
	Component();
	~Component();
};

