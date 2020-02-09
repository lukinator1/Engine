#pragma once
#include "Engine.h"
#include <vector>
#include "Vertex.h"
#include "fstream"
#include <sstream>
class Mesh : public Logger  //add name to to the constructors
{
	unsigned int size; 
	unsigned int indexbufferobject;
public:
	std::string name;
	Mesh(Vertex* vertices, unsigned int * indices, unsigned int numvertices, unsigned int numindices);
	Mesh();
	~Mesh();
	void makeMesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices);
	void drawMesh();
	void addVertices(Vertex* vertices, int numvertices);
	void loadMeshObj(std::string file);
	void makeErrorMesh();
	void normalizeNormalVertices(Vertex * vertices, int numvertices);
	void calculateNormals(Vertex* vertices, unsigned int* indices, unsigned int numvertices, unsigned int numindices);
	GLuint vbo;
	GLuint tbo;
	GLuint ibo;
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