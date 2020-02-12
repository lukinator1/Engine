#pragma once
#include "../Mathlibrary/vector2.h"
#include "../Mathlibrary/vector3.h"
class Vertex
{
private:
	/*Math::vector3 texture;
	Math::vector3 normal;*/
public:
	Vertex();
	Vertex(vector3 positioncoordinates, vector2 texturecoordinates, vector3 newnormal); /*, Math::vector3 texture, Math::vector3 normal*/
	Vertex(vector3 newposition, vector2 newtexture);
	Vertex(vector3 newposition);
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float textx, float texty);
	void setNormal(vector3 newnormal);
	void setNormal(float newx, float newy, float newz);
	~Vertex();
	vector3 position;
	vector2 texture;
	vector3 normal;
};

