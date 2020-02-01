#include "Mesh.h"
Mesh::Mesh(Vertex* vertices, unsigned int numvertices, int numindices)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numvertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*initMesh(vertices, numindices);*/
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);  //delete array here?
}
void Mesh::initMesh(Vertex* vertices, int numvertices) //error message can go here
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numvertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*indices = numvertices;
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
	glGenBuffers(1, vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numvertices, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);*/
}
void Mesh::drawMesh()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	/*glBindVertexArray(0);*/

	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbufferobject);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);*./
	/*glBindVertexArray(vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, indices);
	glBindVertexArray(0);*/
	/*glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0); //skid set to default
	glDrawArrays(GL_TRIANGLES, 0, indices);*/
}
void Mesh::addVertices(Vertex * vertices, int numvertices)
{
	/*size = numvertices;
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, numvertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);*/
	/*glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numvertices, vertices, GL_STATIC_DRAW);*/
}
