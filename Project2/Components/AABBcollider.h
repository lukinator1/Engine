#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
/*class AABBcollider;
void doNothing() {
	std::cout << "test" << std::endl;
}*/
class AABBcollider : public Component
{
public:
	Boundingbox AABB;
	Shader colliderdebugshader;
	vector3 ontransformposition;
	Mesh debugbox;
	Materials debugcollidermaterials;
	Texture collisiontexture;
	Texture sleeptexture;
	bool debugcollidermesh = true;
	bool settotransform;
	void (*collisioncallback)(int);

	void componentPhysics(Transforming &t) {
		if (settotransform) {
			t.position = AABB.getPosition();
			t.rotation = AABB.newrot;
		}
		AABB.collisiondata.otherobjects.clear();
		AABB.collisiondata.momentia.clear();
		if (AABB.collisiondata.forces.size() != 1) {
			AABB.collisiondata.forces.erase(AABB.collisiondata.forces.begin() + 1, AABB.collisiondata.forces.end());
		}
		if (debugcollidermesh) {
			vector3 impulsecolor;
			if (AABB.collided) {
				debugcollidermaterials.texture.textureactive = true;
				debugcollidermaterials.texture = collisiontexture;
				impulsecolor.setVector(0.7f, 0.7f, 0.7f);
			}
			else if (AABB.velocity == vector3(0, 0, 0)) {
				debugcollidermaterials.texture.textureactive = true;
				debugcollidermaterials.texture = sleeptexture;
				impulsecolor.setVector(0.8f, 0.213f, 0.0f);
			}
			else {
				debugcollidermaterials.texture.textureactive = false;
				impulsecolor = (AABB.velocity).multiply(AABB.mass).divide(1000.0f);
			}

			vector3 newscale(AABB.getWidth()/2.0f, AABB.getHeight()/2.0f, AABB.getLength()/2.0f);
			debugcollidermaterials.color = impulsecolor;
			colliderdebugshader.useShader();
			colliderdebugshader.updateUniforms(AABB.collidertransform.newUnprojectedMatrix(newscale), AABB.collidertransform.newTransformationMatrix(newscale), AABB.collidertransform.position, debugcollidermaterials);
			debugbox.drawMesh();
			debugcollidermaterials.texture.textureactive = false;
		}
		//collisioncallback;
		AABB.collided = false;
	}
	void initializeComponent() {	
		colliders.push_back(&AABB);
	}
	void setToTransform(bool trans) {
		settotransform = trans;
	}
	void setOnTransformPosition(vector3 ontransform) {
		ontransformposition = ontransform;
	}
	/*void setCollisionCallback(void* function) {
		collisioncallback = function;
	}*/
	AABBcollider(Boundingbox aabbox) : debugbox("cube.obj"), colliderdebugshader("Colliderdebug"), collisiontexture("Collisiondebug.png"), sleeptexture("Sleepingdebug.png") {
		vector3 impulsecolor = (AABB.velocity).Normalize().multiply(AABB.velocity.multiply(AABB.mass)).divide(1000.0f);
		debugcollidermaterials.color = impulsecolor;
		debugcollidermaterials.texture.textureactive = false;
		AABB = aabbox;
		settotransform = true;
	}
	AABBcollider() : debugbox("cube.obj"), colliderdebugshader("Colliderdebug"), collisiontexture("Collisiondebug.png"), sleeptexture("Sleepingdebug.png") {
		vector3 impulsecolor = (AABB.velocity).multiply(AABB.mass).divide(1000.0f);
		debugcollidermaterials.color = impulsecolor;
		//collisioncallback = doNothing;
		debugcollidermaterials.texture.textureactive = false;
		settotransform = true;
	}
	~AABBcollider() {

	}
};
