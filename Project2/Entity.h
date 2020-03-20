#pragma once
#include <vector>
#include "Rendering/Transforming.h"
#include "Rendering/Shader.h"
#include "Components/Component.h"
class Entity //todo: set parent to transform, remove entity
{
private:
public:
	Transforming transform;
	std::vector <Entity *> children;
	std::vector <Component *> components; //maybe make a map?
	Entity();
	Entity(Transforming t) {
		transform = t;
	}
	Entity(Transforming t, std::vector <Entity *> _children) {
		transform = t;
		for (int i = 0; i < _children.size(); i++) {
			children.push_back(_children[i]);
		}
	}
	Entity(Transforming t, std::vector <Entity *> _children, std::vector <Component *> _component) {
		transform = t;
		for (int i = 0; i < _children.size(); i++) {
			children.push_back(_children[i]);
		}
		for (int i = 0; i < _component.size(); i++) {
			components.push_back(_component[i]);
		}
	}

	~Entity();
	void initializeEntities() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->initializeComponent();
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->initializeEntities();
		}
	}
	void updateEntities() { //deltas passed in here
		for (int i = 0; i < components.size(); i++) {
			components[i]->updateComponent(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->updateEntities();
		}
	}
	void entitiesInput() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->componentInput(transform);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->entitiesInput();
		}
	}
	void renderEntities(Shader *s) {
		for (int i = 0; i < components.size(); i++) {
			components[i]->renderComponent(transform, s);
		}
		for (int i = 0; i < children.size(); i++) {
			children[i]->renderEntities(s);
		}
	}
	void updateEntity() { //deltas passed in here
		for (int i = 0; i < components.size(); i++) {
			components[i]->updateComponent(transform);
		}
	}
	void renderEntity(Shader *s) {
		for (int i = 0; i < components.size(); i++) {
			components[i]->renderComponent(transform, s);
		}
	}
	void entityInput() {
		for (int i = 0; i < components.size(); i++) {
			components[i]->componentInput(transform);
		}
	}
	void removeComponent(Component &component) {
		int counter = 0;
		for (auto i = components.begin(); i != components.end(); i++) {
			if (components[counter] == &component) {
				components.erase(i);
			}
			counter++;
		}
	}
	void addSubEntity(Entity * subentity) {
		children.push_back(subentity);
	}
	void addComponent(Component* component) {
		components.push_back(component);
	}
};

