#pragma once
#include "../Logger.h"
#include "Vertex.h"
#include "fstream"
#include <vector>
#include <sstream>
#include <GL/glew.h>
class Mesh : public Logger 
{
public:
	unsigned int size;
	GLuint vbo;
	GLuint ibo;
	GLuint vao;
	void normalizeNormalVertices(Vertex * vertices, int numvertices);
	void freeMesh();
	void calculateNormals(Vertex* vertices, unsigned int* indices, unsigned int numvertices, unsigned int numindices);
	Mesh(Vertex* vertices, unsigned int * indices, unsigned int numvertices, unsigned int numindices);
	Mesh();
	Mesh(std::string file);
	~Mesh();
	void makeMesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices);
	void makeSkyboxMesh(float* vertices, unsigned int numvertices);
	void drawMesh();
	void drawNoIndicesMesh();
	void loadMeshObj(std::string file);
	void makeErrorMesh();
};
//glBindBuffer(GL_ARRAY_BUFFER, vbo)
//glBufferData(GL_ARRAY_BUFFER, size, data, usage)

//draw
//glEnableVertexAttribArray(0)
//glbindbuffer(GL_ARRAY_BUFFER, vbo)
//glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 *sizeof(float), 0)
//glDrawArrays(GL_TRIANGLES, 0, SIZE)
//glDisableVertexAttribArray(0)