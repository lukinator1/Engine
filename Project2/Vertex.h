#pragma once
#include "Math.h"
#include "vector3.h"
class Vertex
{
private:
	/*Math::vector3 texture;
	Math::vector3 normal;*/
public:
	Vertex();
	Vertex(vector3 position); /*, Math::vector3 texture, Math::vector3 normal*/
	Vertex(float x, float y, float z);
	~Vertex();
	vector3 position;
};

