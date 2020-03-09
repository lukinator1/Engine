#pragma once
#include "Rendering/Transforming.h"
#include "Rendering/Shader.h"
class Component{
public:  //deltas passed in here
	void updateComponent(Transforming t) {

	}
	void componentInput(Transforming t) {

	}
	virtual void renderComponent(Transforming &t, Shader *s) {

	}
	virtual void renderComponent() {

	}
	Component();
	~Component();
};

