#include "Vertex.h"
Vertex::Vertex()
{
}
Vertex::Vertex(vector3 newposition, vector2 newtexture) /*, Math::vector3 texture, Math::vector3 normal*/
{
	position = newposition;
	texture = newtexture;
}
Vertex::Vertex(vector3 newposition) {		//both temporariy/probably will be deleted
	position = newposition;
}
Vertex::Vertex(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
}
Vertex::Vertex(float posx, float posy, float posz, float textx, float texty) {
	position.x = posx;
	position.y = posy;
	position.z = posz;

	texture.x = textx;
	texture.y = texty;
}

Vertex::~Vertex()
{
}
