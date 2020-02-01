#pragma once
#include "Engine.h"
#include "Vertex.h"
class Mesh
{
	int size; 
	unsigned int indexbufferobject;
public:
	Mesh(Vertex* vertices, unsigned int numvertices, int numindices);
	~Mesh();
	void initMesh(Vertex* vertices, int numvertices);
	void drawMesh();
	void addVertices(Vertex* vertices, int numvertices);
	GLuint vbo;
	GLuint vao;
};
//glBindBuffer(GL_ARRAY_BUFFER, vbo)
//glBufferData(GL_ARRAY_BUFFER, size, data, usage)

//draw
//glEnableVertexAttribArray(0)
//glbindbuffer(GL_ARRAY_BUFFER, vbo)
//glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 *sizeof(float), 0)
//glDrawArrays(GL_TRIANGLES, 0, SIZE)
//glDisableVertexAttribArray(0)