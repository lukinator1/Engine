#include "Vertex.h"
Vertex::Vertex()
{
}
Vertex::Vertex(vector3 newposition) /*, Math::vector3 texture, Math::vector3 normal*/
{
	position = newposition;
}
Vertex::Vertex(float newx, float newy, float newz) {
	position.x = newx;
	position.y = newy;
	position.z = newz;
}
Vertex::~Vertex()
{
}
