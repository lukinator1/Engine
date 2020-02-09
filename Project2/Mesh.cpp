#include "Mesh.h"
Mesh::Mesh() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &tbo);
	glGenBuffers(1, &ibo);
	//default/error mesh
}
Mesh::Mesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices)
{
	makeMesh(vertices, indices, numvertices, numindices);
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);  //delete array here?
}
void Mesh::makeMesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices) //error message can go here
{
	size = numindices;
	calculateNormals(vertices, indices, numvertices, numindices);
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
}
void Mesh::drawMesh()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, (void*)0);
	/*glDrawArrays(GL_TRIANGLES, 0, 3);*/
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
void Mesh::loadMeshObj(std::string file) //max size of vector?
{
	std::ifstream fileopener;
	fileopener.open(file);
	std::vector<Vertex>importedvertices;
	std::vector<unsigned int>importedindices;

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
						importedvertices.push_back(Vertex(std::stof(buffer), 0.0f, 0.0f));

						getline(streamer, buffer, ' ');			//y
						importedvertices.back().position.y = stof(buffer);

						getline(streamer, buffer, ' ');			//z
						importedvertices.back().position.z = stof(buffer);
					}

					else if (buffer[0] == 'f' && buffer.size() == 1) {   //indices
						getline(streamer, buffer, '/');				//x1
						importedindices.push_back(stoi(buffer) - 1);
						getline(streamer, buffer, '/');
						/*importedindices.push_back(stoi(buffer) - 1);*/
						getline(streamer, buffer, ' ');
						/*importedindices.push_back(stoi(buffer) - 1);*/

						getline(streamer, buffer, '/');			//x2
						importedindices.push_back(stoi(buffer) - 1);
						getline(streamer, buffer, '/');
						/*importedindices.push_back(stoi(buffer) - 1);*/
						getline(streamer, buffer, ' ');
						/*importedindices.push_back(stoi(buffer) - 1);*/


						getline(streamer, buffer, '/');			//x3
						importedindices.push_back(stoi(buffer) - 1);
						getline(streamer, buffer, '/');
						/*importedindices.push_back(stoi(buffer) - 1);*/
						getline(streamer, buffer, ' ');
						/*importedindices.push_back(stoi(buffer) - 1);*/
						}
					}
				}
			}
		}
	}
	else
	{
		engineLog(__FILE__, __LINE__, "Warning: Model failed to import. Returned an error model.", 2, 2, true);
		return; //error model
	}
	
	if (importedvertices.size() == 0 || importedindices.size() == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Model failed to import. Returned an error model.", 2, 2, true);
	}

	Vertex* vertexarray = &importedvertices[0];
	unsigned int* indexarray = &importedindices[0];

	this->makeMesh(vertexarray, indexarray, importedvertices.size(), importedindices.size());
}
void Mesh::makeErrorMesh() //todo
{
}
void Mesh::calculateNormals(Vertex* vertices, unsigned int* indices, unsigned int numvertices, unsigned int numindices){
	for (unsigned int i = 0; i < numindices; i += 3) {
		unsigned int i0 = indices[i];
		unsigned int i1 = indices[i + 1];
		unsigned int i2 = indices[i + 2];
		vector3 edge1 = vertices[i1].position.subtract(vertices[i0].position);
		vector3 edge2 = vertices[i2].position.subtract(vertices[i0].position);
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
