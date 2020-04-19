#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
#include "../Physics/Raytrace.h"
class Boundingspherecollider : public Component
{
public:
	Boundingsphere boundingsphere;
	Shader colliderdebugshader;
	Mesh debugsphere;
	Materials debugcollidermaterials;
	Texture collisiontexture;
	Texture sleeptexture;
	bool debugcollidermesh = false;
	bool settotransform;
	void componentPhysics(Transforming &t) {
		if (settotransform) {
			t.position = boundingsphere.getPosition();
			t.rotation = boundingsphere.getRotation();
		}
		boundingsphere.collisiondata.otherobjects.clear();
		boundingsphere.collisiondata.momentia.clear();
		if (boundingsphere.collisiondata.forces.size() != 1) {
			boundingsphere.collisiondata.forces.erase(boundingsphere.collisiondata.forces.begin() + 1, boundingsphere.collisiondata.forces.end());
		}
		
		if (debugcollidermesh) {
			vector3 impulsecolor;
			if (boundingsphere.collided) {
				debugcollidermaterials.texture.textureactive = true;
				debugcollidermaterials.texture = collisiontexture;
				impulsecolor.setVector(0.7f, 0.7f, 0.7f);
			}
			else if (boundingsphere.velocity == vector3(0, 0, 0)) {
				debugcollidermaterials.texture.textureactive = true;
				debugcollidermaterials.texture = sleeptexture;
				impulsecolor.setVector(0.8f, 0.213f, 0.0f);
			}
			else {
				debugcollidermaterials.texture.textureactive = false;
				impulsecolor = (boundingsphere.velocity).multiply(boundingsphere.mass).divide(1000.0f);
			}

			vector3 newscale(boundingsphere.radius, boundingsphere.radius, boundingsphere.radius);
			debugcollidermaterials.color = impulsecolor;
			colliderdebugshader.useShader();
			colliderdebugshader.updateUniforms(boundingsphere.collidertransform.newUnprojectedMatrix(newscale), boundingsphere.collidertransform.newTransformationMatrix(newscale), boundingsphere.collidertransform.position, debugcollidermaterials);
			debugsphere.drawMesh();
			debugcollidermaterials.texture.textureactive = false;
		}
		boundingsphere.collided = false;
	}
	void initializeComponent() {
		colliders.push_back(&boundingsphere);
	}
	void setToTransform(bool trans) {
		settotransform = trans;
	}
	Boundingspherecollider(Boundingsphere bsphere) : debugsphere("sphere.obj"), colliderdebugshader("Colliderdebug"), collisiontexture("Collisiondebug.png"), sleeptexture("Sleepingdebug.png") {
		vector3 impulsecolor = (boundingsphere.velocity).multiply(boundingsphere.mass).divide(1000.0f);
		debugcollidermaterials.color = impulsecolor; 
		debugcollidermaterials.texture.textureactive = false;
		boundingsphere = bsphere;
		settotransform = true;
		/*boundingsphere.position = physicstransform.position;
		physicstransform = t;*/
	}
	Boundingspherecollider() : debugsphere("sphere.obj"), colliderdebugshader("Colliderdebug"), collisiontexture("Collisiondebug.png"), sleeptexture("Sleepingdebug.png") {
		vector3 impulsecolor = (boundingsphere.velocity).multiply(boundingsphere.mass).divide(1000.0f);
		debugcollidermaterials.color = impulsecolor;
		debugcollidermaterials.texture.textureactive = false;
		settotransform = true;
		/*boundingsphere.position = physicstransform.position;
		physicstransform = t;*/
	}
	~Boundingspherecollider() {
		collisiontexture.freeTexture();
		sleeptexture.freeTexture();
	}
};
