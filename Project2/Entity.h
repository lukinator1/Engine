#pragma once
#include <vector>
#include "Rendering/Transforming.h"
#include "Component.h"
class Entity
{
private:
public:
	Transforming transform;
	std::vector <Entity> children;
	std::vector <Component *> components; //maybe make a map?
	Entity();
	~Entity();
	void updateEntity() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->updateComponent(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i].updateEntity();
		}
	}
	void entityInput() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->componentInput(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i].entityInput();
		}
	}
	void renderEntity() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->renderComponent(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i].renderEntity();
		}
	}
	void addSubEntity(Entity &subentity) {
		children.push_back(subentity);
	}
	void addComponent(Component* component) {
		components.push_back(component);
	}
};

