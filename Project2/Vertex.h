#pragma once
#include "Engine.h"
class Vertex
{
private:
	/*Math::vector3 texture;
	Math::vector3 normal;*/
public:
	Vertex();
	Vertex(vector3 positioncoordinates, vector2 texturecoordinates); /*, Math::vector3 texture, Math::vector3 normal*/
	Vertex(vector3 newposition);
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float textx, float texty);
	~Vertex();
	vector3 position;
	vector2 texture;
};

