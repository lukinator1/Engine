#pragma once
#include "Texture.h"
#include "../Mathlibrary/vector3.h"
#include <string>
class Materials : public Texture //todo: alphas, change into map
{
public:
	Texture texture;
	vector3 color;
	float alpha;
	float specularintensity;
	float specularexponent;
	Materials() {
		color.setVector(1.0f, 1.0f, 1.0f);
		specularintensity = 2.0f;
		specularexponent = 32.0f;
		alpha = 0.5f;
	}
	Materials(Texture newtexture) {
		texture = newtexture;
		color = vector3(1.0f, 1.0f, 1.0f);
		specularintensity = 2;
		specularexponent = 32;
	}
	Materials(std::string filetexturename) {
		texture = filetexturename;
		color = vector3(1.0f, 1.0f, 1.0f);
		specularintensity = 2;
		specularexponent = 32;
	}
	Materials(Texture &newtexture, vector3 newcolor) {
		texture = newtexture;
		color = newcolor;
		specularintensity = 2;
		specularexponent = 32;
	}
	Materials(std::string filetexturename, vector3 newcolor) {
		texture.loadTexture(filetexturename);
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
	Materials(Texture &newtexture, vector3 newcolor, float newspecintensity, float newspecexponent) {
		texture = newtexture;
		color = newcolor;
		specularintensity = newspecintensity;
		specularexponent = newspecexponent;
	}
	void setMaterial(Texture &newtexture, vector3 newcolor) {
		texture = newtexture;
		color = newcolor;
	}
	void setMaterial(std::string filetexturename, vector3 newcolor) {
		texture.loadTexture(filetexturename);
		color = newcolor;
	}
	void setMaterial(Texture &newtexture, vector3 newcolor, float newspecintensity, float newspecexponent) {
		texture = newtexture;
		color = newcolor;
		specularintensity = newspecintensity;
		specularexponent = newspecexponent;
	}
	void setMaterial(std::string filetexturename, vector3 newcolor, float newspecintensity, float newspecexponent) {
		texture.loadTexture(filetexturename);
		color = newcolor;
		specularintensity = newspecintensity;
		specularexponent = newspecexponent;
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
	void seSpecularIntensity(float newspecintensity) {
		specularintensity = newspecintensity;
	}
	void setSpecularExponent(float newspecexponent){
		specularexponent = newspecexponent;
	}
	vector3 getColor(){
		return color;
	}
	float getAlpha() {
		return alpha;
	}
	float getSpecularIntensity() {
		return specularintensity;
	}
	float getSpecularExponent() {
		return specularexponent;
	}
	void freeMaterial() {
		texture.freeTexture();
		color = vector3(1.0f, 1.0f, 1.0f);
		alpha = 0.5f;
		specularintensity = 2.0f;
		specularexponent = 32.0f;
	}
	void loadMTL(std::string filename) {
		std::ifstream fileopener;
		fileopener.open("Rendering/Materials/" + filename);
		
	}
	~Materials();
};

