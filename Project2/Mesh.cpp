#include "Mesh.h"
Mesh::Mesh(Vertex* vertices)
{
	initMesh(vertices, 3);
}
Mesh::~Mesh()
{
	glDeleteBuffers(4, vertexArrayBuffers);
	glDeleteVertexArrays(1, &vertexArrayObject);
}
void Mesh::initMesh(Vertex* vertices, unsigned int numvertices)
{
	indices = numvertices;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numvertices, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
}
void Mesh::drawMesh()
{
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, indices);
	glBindVertexArray(0);
	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //skid set to default
	glDrawArrays(GL_TRIANGLES, 0, indices);*/
}
