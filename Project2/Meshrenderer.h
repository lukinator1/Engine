#pragma once
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/Materials.h"
#include "Rendering/Transforming.h"
#include "Component.h"
class Meshrenderer : public Component
{
public:
	Mesh mesh;
	Materials materials;
	Shader shader;
	Meshrenderer(Mesh &mesh, Materials &materials) {
		this->mesh = mesh;
		this->materials = materials;
	}
	~Meshrenderer();
	void renderComponent(Transforming transform, Shader shader) {
		transform.setTranslationVector(vector3(10.0f, 17.5f, 12.0f));
		shader.useShader();
		shader.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, materials);
		mesh.drawMesh();
	}
};

