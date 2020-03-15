#pragma once
#include "Component.h"
#include "../Rendering/Lighting/Lighting.h"
#include "../Rendering/Shader.h"
#include "../Rendering/Transforming.h"
class Directionallightc : public Component
{
public:
	Directionallight directionallight;
	Directionallightc (Directionallight &dl) {
		directionallight = dl;
	}
	void renderComponent(Transforming &transform, Shader * &shader) {
		/*shader->directionallight = directionallight;
		shader->updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, *materials);
		mesh->drawMesh();*/
	}
	~Directionallightc();
};


