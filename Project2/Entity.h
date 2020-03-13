#pragma once
#include <vector>
#include "Rendering/Transforming.h"
#include "Rendering/Shader.h"
#include "Component.h"
class Entity //set parent to transform
{
private:
public:
	Transforming transform;
	std::vector <Entity *> children;
	std::vector <Component *> components; //maybe make a map?
	Entity();
	~Entity();
	void updateEntity() { //deltas passed in here
		for (int i = 0; i < components.size(); i++) {
			components[i]->updateComponent(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->updateEntity();
		}
	}
	void entityInput() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->componentInput(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->entityInput();
		}
	}
	void renderEntity(Shader *s) {
		for (int i = 0; i < components.size(); i++) {
			components[i]->renderComponent(transform, s);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->renderEntity(s);
		}
	}
	void addSubEntity(Entity * subentity) {
		children.push_back(subentity);
	}
	void addComponent(Component* component) {
		components.push_back(component);
	}
};

