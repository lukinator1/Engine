#pragma once
#include "Texture.h"
#include "vector3.h"
#include <string>
class Materials : public Texture //todo: alphas
{
public:
	Texture texture;
	vector3 color;
	float alpha;
	Materials() {
		/*texture = texture.errortexture */
		color.setVectorThree(0.0f, 0.0f, 0.0f);
		alpha = 0.5f;
	}
	Materials(Texture newtexture, vector3 newcolor) {
		texture = newtexture;
		color = newcolor;
	}
	Materials(std::string filetexturename, vector3 newcolor) {
		texture.loadTexture(filetexturename);
		color = newcolor;
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

