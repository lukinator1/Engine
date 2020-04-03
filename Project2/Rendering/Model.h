#pragma once
#include "Mesh.h"
#include "Materials.h"
#include "Shader.h"
#include <vector>
#include <map>
class Model : public Logger
{
public:
	std::vector <Mesh> meshes;
	std::vector <Materials> materials;
	void normalizeNormalVertices(Vertex * vertices, int numvertices);
	void freeModel();
	void calculateNormals(Vertex* vertices, unsigned int* indices, unsigned int numvertices, unsigned int numindices);
	/*Mesh(Vertex* vertices, unsigned int * indices, unsigned int numvertices, unsigned int numindices);*/
	Model(std::string file);
	/*void makeMesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices);*/
	void drawModel(Shader& s);
	/*void drawNoIndicesMesh();*/
	void loadModelObj(std::string file);
	void makeErrorModel();
	Model();
	~Model();
};

