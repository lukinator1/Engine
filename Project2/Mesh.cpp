#include "Mesh.h"
Mesh::Mesh() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
}
Mesh::Mesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices)
{
	size = numindices;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numvertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numindices, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	/*initMesh(vertices, numindices);*/
}
Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);  //delete array here?
}
void Mesh::makeMesh(Vertex* vertices, unsigned int *indices, unsigned int numvertices, unsigned int numindices) //error message can go here
{
	size = numindices;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numvertices, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numindices, indices, GL_STATIC_DRAW);

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
