#include "Vertex.h"
Vertex::Vertex()
{
	texture = vector2(0.0f, 0.0f);
}
Vertex::Vertex(vector3 newposition, vector2 newtexture, vector3 newnormal)
{
	position = newposition;
	texture = newtexture;
	normal = newnormal;
}
Vertex::Vertex(vector3 newposition, vector2 newtexture)
{
	position = newposition;
	texture = newtexture;
	normal = vector3(0.0f, 0.0f, 0.0f);
}
Vertex::Vertex(vector3 newposition) {		//both temporariy/probably will be deleted
	position = newposition;
	texture = vector2(0.0f, 0.0f);
}
Vertex::Vertex(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	texture = vector2(0.0f, 0.0f);
}
Vertex::Vertex(float posx, float posy, float posz, float textx, float texty) {
	position.x = posx;
	position.y = posy;
	position.z = posz;

	texture.x = textx;
	texture.y = texty;
}
void Vertex::setNormal(vector3 newnormal) {
	normal = newnormal;
}
void Vertex::setNormal(float newx, float newy, float newz) {
	normal.x = newx;
	normal.y = newy;
	normal.z = newz;
}
Vertex::~Vertex()
{
}
