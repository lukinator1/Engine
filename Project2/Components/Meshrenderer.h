#pragma once
#include "../Rendering/Mesh.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Materials.h"
#include "../Rendering/Transforming.h"
#include "Component.h"
class Meshrenderer : public Component
{
public:
	Mesh *mesh;
	Materials *materials;
	Meshrenderer(Mesh &mesh, Materials &materials) {
		this->mesh = &mesh;
		this->materials = &materials;
	}
	~Meshrenderer();
	void setMesh(Mesh &mesh) {
		this->mesh = &mesh;
	}
	void setMaterials(Materials &materials) {
		this->materials = &materials;
	}
	void renderComponent(Transforming &transform, Shader * &shader) {
		shader->useShader();
		shader->updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, *materials);
		mesh->drawMesh();
	}
};

