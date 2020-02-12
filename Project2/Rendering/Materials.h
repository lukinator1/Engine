#pragma once
#include "Texture.h"
#include "../Mathlibrary/vector3.h"
#include <string>
class Materials : public Texture //todo: alphas
{
public:
	Texture texture;
	vector3 color;
	float alpha;
	float specularintensity;
	float specularexponent;
	Materials() {
		/*texture = texture.errortexture */
		color.setVectorThree(0.0f, 0.0f, 0.0f);
		specularintensity = 2.0f;
		specularexponent = 32.0f;
		alpha = 0.5f;
	}
	Materials(Texture newtexture, vector3 newcolor) {
		texture = newtexture;
		color = newcolor;
		specularintensity = 2;
		specularexponent = 32;
	}
	Materials(std::string filetexturename, vector3 newcolor, float newspecintensity, float newspecexponent) {
		texture.loadTexture(filetexturename);
		color = newcolor;
		specularintensity = newspecintensity;
		specularexponent = newspecexponent;
	}
	Materials(std::string filetexturename, vector3 newcolor) {
		texture.loadTexture(filetexturename);
		color = newcolor;
		specularintensity = 2;
		specularexponent = 32;
	}
	void setMaterial(Texture newtexture, vector3 newcolor) {
		texture = newtexture;
		color = newcolor;
	}
	void setMaterial(std::string filetexturename, vector3 newcolor) {
		texture.loadTexture(filetexturename);
		color = newcolor;
	}
	void setTexture(Texture newtexture) {
		texture = newtexture;
	}
	void setColor(vector3 newcolor) {
		color = newcolor;
	}
	void setColor(vector3 newcolor, float newalpha) {
		color = newcolor;
		alpha = newalpha;
	}
	void setAlpha(float newalpha) {
		alpha = newalpha;
	}
	Texture getTexture() {
		return texture;
	}
	vector3 getColor(){
		return color;
	}
	float getAlpha() {
		return alpha;
	}
	~Materials();
};

