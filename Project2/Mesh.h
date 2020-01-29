#pragma once
#include "Engine.h"
#include "Vertex.h"
class Mesh
{		//vbo
		//getting size of mesh
public:
	Mesh(Vertex* vertices);
	~Mesh();
	void initMesh(Vertex* vertices, unsigned int numvertices);
	void drawMesh();
	unsigned int indices;
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[4];

};
//glBindBuffer(GL_ARRAY_BUFFER, vbo)
//glBufferData(GL_ARRAY_BUFFER, size, data, usage)

//draw
//glEnableVertexAttribArray(0)
//glbindbuffer(GL_ARRAY_BUFFER, vbo)
//glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 *sizeof(float), 0)
//glDrawArrays(GL_TRIANGLES, 0, SIZE)
//glDisableVertexAttribArray(0)