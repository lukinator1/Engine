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
	~Entity();
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

