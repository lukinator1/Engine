/*#include "Window.h"
#include "Engine.h"
#include "Input.h"
#include "Mesh.h"
#include "Shader.h"
#include "Materials.h"
#include "Texture.h"
#include "Directionallight.h"
#include "Transforming.h"
#include "Scene.h"
#include "Memorymanager.h"
#include "Messaging.h"
#include <fstream>
#include <iostream>
using namespace SS;
	int main(int argc, char* argv[]) {
		/*Vertex vertices[] = half pyramid
		{					//position, texture
			Vertex(vector3(-1.0f, -1.0f, 0.0f), vector2(0.0f,0.0f)),
			Vertex(vector3(0.0f, 1.0, 0.0f), vector2(0.5f , 0.0f)),
			Vertex(vector3(1.0f, -1.0f, 0.0f), vector2(1.0f, 0.0f)),
			Vertex(vector3(0.0f, -1.0f, 1.0f), vector2(0.0f, 0.5f))
		};
		unsigned int indices[] = {
			3, 1, 0,
			2, 1, 3,
			0, 1, 2,
			0, 2, 3
		};
		/*Vertex vertices[] =
		{Vertex(vector3(-1.0f, -1.0f, 0.5773f), vector2(0.0f, 0.0f)),
		Vertex(vector3(0.0f, -1.0f, -1.15475f), vector2(0.5f, 0.0f)),
		Vertex(vector3(1.0f, -1.0f, 0.5773f), vector2(1.0f, 0.0f)),
		Vertex(vector3(0.0f, 1.0f, 0.0f), vector2(0.5f, 1.0f))};

		unsigned int indices[] = { 0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		1, 2, 0 };
		Engine engine;
		Scene newscene;
		float fieldDepth = 10.0f;
		float fieldWidth = 10.0f;
		Vertex vertices[] = { Vertex(vector3(-fieldWidth, 0.0f, -fieldDepth), vector2(0.0f, 0.0f)),
							Vertex(vector3(-fieldWidth, 0.0f, fieldDepth * 3), vector2(0.0f, 1.0f)),
							Vertex(vector3(fieldWidth * 3, 0.0f, -fieldDepth), vector2(1.0f, 0.0f)),
							Vertex(vector3(fieldWidth * 3, 0.0f, fieldDepth * 3), vector2(1.0f, 1.0f)) };

		unsigned int indices[] = { 0, 1, 2,
						  2, 1, 3 };
		Mesh meshme(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));
		Mesh quote;
		quote.loadMeshObj("Models/quote.obj");
		/*Spotlight flashlight(vector3(0.9f, 0.9f, 0.9f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 3.5f, 0.0f, 0.1f);
		Spotlight flashlight(vector3(0.0f, 1.0f, 1.0f), vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);

		Shader shaderit;
		/*Texture text;
		text.loadTexture("Textures/test.png");
		shaderit.addVertexShader(shaderit.loadShader("Shaders/Phongvertexshader.vs"));
		shaderit.addFragmentShader(shaderit.loadShader("Shaders/Phongfragmentshader.fs"));
		shaderit.compileShader();
		shaderit.addUniform("cameraposition");
		shaderit.addUniform("color");
		shaderit.addUniform("transform");
		shaderit.addUniform("projectedtransform");
		shaderit.addUniform("uniformFloat");
		shaderit.addUniform("ambientlight");
		shaderit.addUniform("specularintensity");
		shaderit.addUniform("specularexponent");
		shaderit.addUniform("directionallight");
		shaderit.addUniform("pointlights");
		shaderit.addUniform("spotlights");
		shaderit.setAmbientLight(vector3(0.1f, 0.1f, 0.1f));
		shaderit.directionallight = Directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.1f);
		Pointlight *plights = new Pointlight[6];
		plights[0] = Pointlight(vector3(1.0f, 0.5f, 0.0f), vector3(-2.0f, 0.0f, 5.0f), 4.0f, 0.8f, 0.0f, 1.0f);
		plights[1] = Pointlight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 0.8f, 0.0f, 1.0f);
		shaderit.getPointLights()[0] = &plights[0];
		shaderit.getPointLights()[1] = &plights[1];
		Spotlight *slights = new Spotlight[1];

		slights[0] = Spotlight(vector3(0.0f, 1.0f, 1.0f), vector3(-2.0f, 0.0f, 5.0f), vector3(1.0f, 1.0f, 1.0f), 30.0f, 0.7f, 0.8f, 0.0f, 0.1f);
		shaderit.getSpotLights()[0] = &slights[0];
		Materials material("Textures/test.png", vector3(1.0f, 1.0f, 1.0f), 1.0f, 8.0f);		// from basicshader change to render manager startup?


		float previousscrolldistance;
		float unitest = 0.0f;
		int framerate = 0;
		double framecounter = 0;
		engine.thecamera.setMouseLook(true);
		int counter = 0;
		bool flashlighton = false;
		bool lastpressed = false;
		bool pressed = false;
		if (Inputs.keyboardstate[Input::W] == 1) {
			thecamera.moveCamera(thecamera.getForwardvector(), .3f);
		}
		if (Inputs.keyboardstate[Input::A] == 1) {
			thecamera.moveCamera(thecamera.getLeftVector(), .3f);
		}
		if (Inputs.keyboardstate[Input::S] == 1) {
			thecamera.moveCamera(thecamera.getForwardvector(), -.3f);
		}
		if (Inputs.keyboardstate[Input::D] == 1) {
			thecamera.moveCamera(thecamera.getLeftVector(), -.3f);
		}
		if (Inputs.keyboardstate[Input::keyup] == 1) {
			thecamera.rotateCamera(0.0f, 2.0f);
		}
		if (Inputs.keyboardstate[Input::keyleft] == 1) {
			thecamera.rotateCamera(-2.0f, 0.0f);
		}
		if (Inputs.keyboardstate[Input::keydown] == 1) {
			thecamera.rotateCamera(0.0f, -2.0f);
		}
		if (Inputs.keyboardstate[Input::keyright] == 1) {
			thecamera.rotateCamera(2.0f, 0.0f);
		}
		if (Inputs.keyboardstate[Input::L] == 1) {  //flashlight 
			if (lastpressed == false) {
				if (flashlighton == true) {
					flashlight.setIntensity(0.0f);
					flashlighton = false;
				}
				else if (flashlighton == false) {
					flashlight.setIntensity(3.0f);
					flashlighton = true;
				}
				lastpressed = true;
			}
		}
		else {
			lastpressed = false;
		}

		if (Inputs.getScrolldistance().y != 0) {
			thecamera.Zoom(Inputs.getScrolldistance().y);
		}
		if (Inputs.getMouseMovementDistance().x != 0 || Inputs.getMouseMovementDistance().y != 0) {
			thecamera.rotateCamera(Inputs.getXMouseMovementDistance(), Inputs.getYMouseMovementDistance());
		}


		shaderit.setUniform("uniformFloat", (float)sin(unitest));
		transform.setTranslationVector(vector3(0.0f, -1.0f, 5.0f));
		/*transform.setRotationVector(vector3(0, (float)sin(unitest) * 180, 0));
		plights[0].setPosition(vector3(3.0f, 0.0f, 8.0 * (float)(sin(unitest) + 1.0f / 2.0f) + 10.0f));
		plights[1].setPosition(vector3(7.0f, 0.0f, 8.0 * (float)(cos(unitest) + 1.0f / 2.0f) + 10.0f));
		slights[0].setPosition(thecamera.getCameraposition());
		slights[0].setDirection(thecamera.forwardvector);
		transform.setPerspectiveProjectionSettings(thecamera.fov, window.getWindowWidth(), window.getWindowHeight(), thecamera.minviewdistance, thecamera.maxviewdistance);  //integer -> float
		/*transform.setScalingVector(vector3(.75 * sin(unitest), .75 * sin(unitest), .75 * sin(unitest)));
		shaderit.useShader();
		/*shaderit.setUniform("transform", transform.newTransformationMatrix());
		shaderit.setUniform("color", vector3(0.0f, 1.0f, 1.0f));
		text.bindTexture();
		shaderit.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, material);
		meshme.drawMesh();
	}
	void startGame() {

	}
	void updateGame() {
	}
	void endGame() {
	}*/