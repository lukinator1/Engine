#include "Mesh.h"
//#include <algorithm>
Mesh::Mesh() {
	size = 0;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	//default/error mesh
}
Mesh::Mesh(std::string file) { //
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	loadMeshObj(file);
}
Mesh::Mesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices)
{
	makeMesh(vertices, indices, numvertices, numindices);
}
Mesh::~Mesh()
{
	/*freeMesh();*/
}
void Mesh::makeMesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices) //error message can go here
{
	size = numindices;
	/*calculateNormals(vertices, indices, numvertices, numindices);*/
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numvertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);  //change 8 * size of float to size of vertex?
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)sizeof(Vertex::position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(sizeof(Vertex::position) + sizeof(Vertex::texture)));
	glEnableVertexAttribArray(2);
	/*glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex::texture) * numvertices, vertices, GL_STATIC_DRAW);*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numindices, indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::makeSkyboxMesh(float* vertices, unsigned int numvertices) //error message can go here
{
	size = numvertices;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numvertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);  
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::drawMesh()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}
void Mesh::drawNoIndicesMesh() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glBindVertexArray(0);
}
void Mesh::loadMeshObj(std::string file) //max size of vector?
{
	std::ifstream fileopener;
	fileopener.open("Rendering/Models/" + file);
	std::vector<Vertex>importedvertices;
	std::vector<vector3>positioncoordinates;
	std::vector<vector2>texturecoordinates;
	std::vector<vector3>normals;
	std::vector<unsigned int>positionindices;
	std::vector<unsigned int>textureindices;
	std::vector<unsigned int>normalindices;
	std::vector<unsigned int>indices;

	int texturecounter = 0;
	if (fileopener.is_open()) {
		std::string bigbuffer;
		std::string buffer;
		while (getline(fileopener, bigbuffer)) {
			if (fileopener.bad()) {
				engineLog(__FILE__, __LINE__, "Warning: Model failed to import. An error model was returned instead.", 2, 2, true);
				return; //make an error model
			}

			if (!bigbuffer.empty()) {
				std::stringstream streamer(bigbuffer);
				while (getline(streamer, buffer, ' ')) {
					if (!buffer.empty()){
					if (buffer[0] == '#') {
						continue;
					}
					/*if (buffer[0] == 'o' && buffer.size() == 1) { //may be broken
						while (getline(streamer, buffer, ' ')) {
							name.append(buffer);
						}
					}*/
					else if (buffer[0] == 'v' && buffer.size() == 1) {   //vertices
						getline(streamer, buffer, ' ');			//x
						while (buffer == "") {				//eliminate whitespaces
							getline(streamer, buffer, ' ');
						}
						positioncoordinates.push_back(vector3(stof(buffer), 0.0f, 0.0f));
						/*importedvertices.push_back(Vertex(stof(buffer), 0.0f, 0.0f));*/

						getline(streamer, buffer, ' ');			//y
						while (buffer == "") {				
							getline(streamer, buffer, ' ');
						}
						positioncoordinates.back().y = stof(buffer);
						/*importedvertices.back().position.y = stof(buffer);*/
						
					
						getline(streamer, buffer, ' ');			//z
						while (buffer == "") {
							getline(streamer, buffer, ' ');
						}
						positioncoordinates.back().z = stof(buffer);
						/*importedvertices.back().position.z = stof(buffer);*/
					}

					else if (buffer[0] == 'v' && buffer.size() == 2) {   //texture coordinates
						if (buffer[1] == 't') {
							getline(streamer, buffer, ' ');			//u
							while (buffer == "") {				//eliminate whitespaces
								getline(streamer, buffer, ' ');
							}
							texturecoordinates.push_back(vector2(stof(buffer), 0.0f));

							getline(streamer, buffer, ' ');			//v
							while (buffer == "") {
								getline(streamer, buffer, ' ');
							}
							texturecoordinates.back().y = stof(buffer);
						}
						if (buffer[1] == 'n') {
							getline(streamer, buffer, ' ');			//x
							while (buffer == "") {				//eliminate whitespaces
								getline(streamer, buffer, ' ');
							}
							normals.push_back(vector3(stof(buffer), 0.0f, 0.0f));
							/*importedvertices.push_back(Vertex(stof(buffer), 0.0f, 0.0f));*/

							getline(streamer, buffer, ' ');			//y
							while (buffer == "") {
								getline(streamer, buffer, ' ');
							}
							normals.back().y = stof(buffer);
							/*importedvertices.back().position.y = stof(buffer);*/


							getline(streamer, buffer, ' ');			//z
							while (buffer == "") {
								getline(streamer, buffer, ' ');
							}
							normals.back().z = stof(buffer);
						}
						/*importedvertices.back().position.z = stof(buffer);*/
					}

					else if (buffer[0] == 'f' && buffer.size() == 1) {   //indices
						if (texturecoordinates.size() == 0 && normals.size() == 0) {
							getline(streamer, buffer, ' ');				//x1
							positionindices.push_back(stoi(buffer) - 1);
							getline(streamer, buffer, ' ');				//x2
							positionindices.push_back(stoi(buffer) - 1);
							getline(streamer, buffer, ' ');				//x3
							positionindices.push_back(stoi(buffer) - 1);
						}
						else if (texturecoordinates.size() > 0 && normals.size() == 0){
							getline(streamer, buffer, '/');				//x1
							positionindices.push_back(stoi(buffer) - 1);
							getline(streamer, buffer, ' ');
							textureindices.push_back(stoi(buffer) - 1);

							getline(streamer, buffer, '/');
							positionindices.push_back(stoi(buffer) - 1);
							getline(streamer, buffer, ' ');
							textureindices.push_back(stoi(buffer) - 1);


							getline(streamer, buffer, '/');			//x3
							positionindices.push_back(stoi(buffer) - 1);
							getline(streamer, buffer, ' ');
							textureindices.push_back(stoi(buffer) - 1);
						}
					else if (texturecoordinates.size() > 0 && normals.size() > 0) {
					getline(streamer, buffer, '/');				//x1
					positionindices.push_back(stoi(buffer) - 1);
					getline(streamer, buffer, '/');
					textureindices.push_back(stoi(buffer) - 1);
					getline(streamer, buffer, ' ');
					normalindices.push_back(stoi(buffer) - 1);

					getline(streamer, buffer, '/');
					positionindices.push_back(stoi(buffer) - 1);
					getline(streamer, buffer, '/');
					textureindices.push_back(stoi(buffer) - 1);
					getline(streamer, buffer, ' ');
					normalindices.push_back(stoi(buffer) - 1);


					getline(streamer, buffer, '/');			//x3
					positionindices.push_back(stoi(buffer) - 1);
					getline(streamer, buffer, '/');
					textureindices.push_back(stoi(buffer) - 1);
					getline(streamer, buffer, ' ');
					normalindices.push_back(stoi(buffer) - 1);
						}
					}
					}
				}
			}
		}
	}
	else
	{
		engineLog(__FILE__, __LINE__, "Warning: Model failed to import. Returned an error model.", 2, 2, true);
		return; //todo: error model
	}
	
	if (positioncoordinates.size() == 0 || positionindices.size() == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Model failed to import. Returned an error model.", 2, 2, true);
		return;
	}

	for (int i = 0; i < positionindices.size(); i++) { 
	importedvertices.push_back(Vertex(vector3(positioncoordinates[positionindices[i]])));
	importedvertices.back().texture = texturecoordinates[textureindices[i]];
	importedvertices.back().normal = normals[normalindices[i]];
	indices.push_back(i);
	}

/*	auto optimize = std::unique(importedvertices.begin(), importedvertices.end()); //todo: optimize
	importedvertices.erase(optimize, importedvertices.end());

	for (unsigned int i = 0; i < importedvertices.size(); i++) {
		indices.push_back(i);
	}*/

	Vertex* vertexarray = &importedvertices[0];
	unsigned int* indexarray = &indices[0];

	this->makeMesh(vertexarray, indexarray, importedvertices.size(), indices.size());
}
void Mesh::makeErrorMesh() //todo
{
}
void Mesh::calculateNormals(Vertex* vertices, unsigned int* indices, unsigned int numvertices, unsigned int numindices){
	for (unsigned int i = 0; i < numindices; i += 3) {
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];
		vector3 edge1 = vertices[i1].position.Subtract(vertices[i0].position);
		vector3 edge2 = vertices[i2].position.Subtract(vertices[i0].position);
		vector3 normal = (edge1.crossProduct(edge2)).Normalize();

		vertices[i0].normal = vertices[i0].normal.add(normal);
		vertices[i1].normal = vertices[i1].normal.add(normal);
		vertices[i2].normal = vertices[i2].normal.add(normal);
	}
		normalizeNormalVertices(vertices, numvertices);
		/*int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		vector3 edge1 = vertices[i1].position.subtract(vertices[i0].position);
		vector3 edge2 = vertices[i2].position.subtract(vertices[i0].position);

		vector3 normal = (edge1.crossProduct(edge2)).Normalize();*/
}
void Mesh::normalizeNormalVertices(Vertex *vertices, int numvertices) {
	for (int i = 0; i < numvertices; i++) {
		vertices[i].normal = (vertices[i].normal).Normalize();
	}
}
void Mesh::freeMesh() {
	size = 0;
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &vao);  //delete array here?
	glDeleteBuffers(1, &ibo);
}
