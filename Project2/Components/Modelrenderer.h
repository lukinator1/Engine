#pragma once
#include "../Rendering/Model.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Transforming.h"
#include "Component.h"
class Modelrenderer : public Component
{
public:
	Model *model;

	Modelrenderer(Model &model) {
		this->model = &model;
	}
	~Modelrenderer();
	void setModel(Model &model) {
		this->model = &model;
	}
	void renderComponent(Transforming &transform, Shader * &shader) {
		shader->useShader();
		for (int i = 0; i < model->meshes.size(); i++) {
			shader->updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, model->materials[i]);
			model->meshes[i].drawMesh();
		}
	}
};



