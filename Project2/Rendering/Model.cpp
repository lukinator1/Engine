#include "Model.h"
#include "Shader.h"
void Model::freeModel()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].first.freeMesh();
	}
	for (auto i = materials.begin(); i != materials.end(); i++) { 
	i->second.freeMaterial();
	}
	meshes.clear();
	materials.clear();
}
Model::Model(std::string file)
{
	materials.emplace("", Materials());
	loadModelObj(file);
}
/*void Model::drawModel(Shader &s)
{
	for (auto i = components.begin(); i != components.end; i++) {
		shader->useShader();
		shader->updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, *materials);
		meshes[i].drawMesh();
	}
}*/
void Model::loadModelObj(std::string file) //max size of vector?
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
	bool meshdone = true;
	bool comment = false;
	std::string matname = "";

	int texturecounter = 0;
	if (fileopener.is_open()) {
		std::string bigbuffer;
		std::string buffer;
		while (getline(fileopener, bigbuffer)) {
			comment = false;
			if (fileopener.bad()) {
				engineLog(__FILE__, __LINE__, "Warning: Model did not fully import.", 2, 2, true);
				return; //make an error model
			}

			if (!bigbuffer.empty()) {
				std::stringstream streamer(bigbuffer);
				while (getline(streamer, buffer, ' ') && !comment) {
					if (!buffer.empty()) {

						if (buffer[0] == '#' || buffer[0] == 'o') {
							comment = true;
							continue;
						}

						if (buffer[0] == 'f' && buffer.size() == 1) {   //indices
							meshdone = true;
							if (texturecoordinates.size() == 0 && normals.size() == 0) {
								getline(streamer, buffer, ' ');				//x1
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');				//x2
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');				//x3
								positionindices.push_back(stoi(buffer) - 1);
							}
							else if (texturecoordinates.size() > 0 && normals.size() == 0) {
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
							else if (texturecoordinates.size() == 0 && normals.size() > 0) {
								getline(streamer, buffer, '/');				//x1
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								getline(streamer, buffer, ' ');
								normalindices.push_back(stoi(buffer) - 1);

								getline(streamer, buffer, '/');
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								getline(streamer, buffer, ' ');
								normalindices.push_back(stoi(buffer) - 1);


								getline(streamer, buffer, '/');			//x3
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								getline(streamer, buffer, ' ');
								normalindices.push_back(stoi(buffer) - 1);
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
							continue;
						}

						if (meshdone && positionindices.size() != 0) {
							for (int i = 0; i < positionindices.size(); i++) {	//mesh ready to load
								importedvertices.push_back(Vertex(vector3(positioncoordinates[positionindices[i]])));
								if (texturecoordinates.size() != 0) {
									importedvertices.back().texture = texturecoordinates[textureindices[i]];
								}
								if (normals.size() != 0) {
									importedvertices.back().normal = normals[normalindices[i]].Normalize();
								}
								indices.push_back(i);
							}
							if (normals.size() == 0) {
								calculateNormals(&importedvertices[0], &indices[0], importedvertices.size(), indices.size());
							}
							/*std::vector<vector3> oldnormals;
							for (int i = 0; i < importedvertices.size(); i++) {
								oldnormals.push_back(importedvertices[i].normal);
							}
							calculateNormals(&importedvertices[0], &indices[0], importedvertices.size(), indices.size());
							for (int i = 0; i < importedvertices.size(); i++) {
								if (oldnormals[i] != importedvertices[i].normal) {
									std::cout << "hello";
								}
							}*/
							Mesh mesh(&importedvertices[0], &indices[0], importedvertices.size(), indices.size());
							meshes.push_back(std::pair<Mesh, std::string>(mesh, matname));
							matname = "";
							positionindices.clear();
							textureindices.clear();
							normalindices.clear();
							importedvertices.clear();
							indices.clear();
							meshdone = false;
						}

						if (buffer[0] == 'm') { //todo: multiple libraries
							if (buffer == "mtllib") {
								getline(streamer, buffer);
								loadMaterials(buffer);
							}
						}

						else if (buffer[0] == 'v' && buffer.size() == 1) {   //vertices
							getline(streamer, buffer, ' ');			//x
							while (buffer == "") {				//eliminate whitespaces
								getline(streamer, buffer, ' ');
							}
							positioncoordinates.push_back(vector3(stof(buffer), 0.0f, 0.0f));

							getline(streamer, buffer, ' ');			//y
							while (buffer == "") {
								getline(streamer, buffer, ' ');
							}
							positioncoordinates.back().y = stof(buffer);


							getline(streamer, buffer, ' ');			//z
							while (buffer == "") {
								getline(streamer, buffer, ' ');
							}
							positioncoordinates.back().z = stof(buffer);
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
								texturecoordinates.back().y = -stof(buffer);
							}
							if (buffer[1] == 'n') {
								getline(streamer, buffer, ' ');			//x
								while (buffer == "") {				//eliminate whitespaces
									getline(streamer, buffer, ' ');
								}
								normals.push_back(vector3(stof(buffer), 0.0f, 0.0f));

								getline(streamer, buffer, ' ');			//y
								while (buffer == "") {
									getline(streamer, buffer, ' ');
								}
								normals.back().y = stof(buffer);


								getline(streamer, buffer, ' ');			//z
								while (buffer == "") {
									getline(streamer, buffer, ' ');
								}
								normals.back().z = stof(buffer);
							}
						}

						else if (buffer[0] == 'u' && buffer.size() == 6)
						{
							if (buffer.substr(0, 6) == "usemtl") {
								getline(streamer, buffer);
								matname = buffer;
							}
						}

						else if (buffer[0] == 'g')
						{
						/*if (buffer.substr(0, 6) == "usemtl") {
							getline(streamer, buffer);
							matname = buffer;
						}
						meshdone = true;*/
						}
						
					}
				}
			}
		}
	}
	else
	{
		engineLog(__FILE__, __LINE__, "Warning: Model failed to import. Returned an error model.", 2, 2, true);
		meshes.push_back(std::pair<Mesh, std::string>(Mesh(), ""));
		return; //todo: error model
	}
	if (meshdone && positionindices.size() != 0) {
		for (int i = 0; i < positionindices.size(); i++) {	//mesh ready to load
			importedvertices.push_back(Vertex(vector3(positioncoordinates[positionindices[i]])));
			if (texturecoordinates.size() != 0) {
				importedvertices.back().texture = texturecoordinates[textureindices[i]];
			}
			if (normals.size() != 0) {
				importedvertices.back().normal = normals[normalindices[i]].Normalize();
			}
			indices.push_back(i);
		}
		if (normals.size() == 0) {
			calculateNormals(&importedvertices[0], &indices[0], importedvertices.size(), indices.size());
		}
		Mesh mesh(&importedvertices[0], &indices[0], importedvertices.size(), indices.size());
		meshes.push_back(std::pair<Mesh, std::string>(mesh, matname));
		matname = "";
	}
	bool there = false;
	for (int i = 0; i < meshes.size(); i++) {	//check to see if material loaded successfully
		there = false;
		for (auto u = materials.begin(); u != materials.end(); u++) {
			if (meshes[i].second == u->first) {
				there = true;
			}
		}
		if (there == false) {
			meshes[i].second = "";
		}
	}
}
void Model::loadMaterials(std::string filename) {
	std::ifstream fileopener;
	std::string matname;
	fileopener.open("Rendering/Materials/" + filename);

	if (fileopener.is_open()) {
		std::string bigbuffer;
		std::string buffer;
		while (getline(fileopener, bigbuffer)) {
			if (fileopener.bad()) {
				engineLog(__FILE__, __LINE__, "Warning: Material failed to import. A default error material was returned instead.", 2, 2, true);
				return; //make an error model
			}

			if (!bigbuffer.empty()) {
				std::stringstream streamer(bigbuffer);
				while (getline(streamer, buffer, ' ')) {
					if (!buffer.empty()) {

						while ((buffer[0] == '\t' || buffer[0] == ' ') && buffer.size() != 0) {
							buffer.erase(buffer.begin());
						}

						if (buffer.empty()) {
							continue;

						}

						if (buffer[0] == '#') {
							continue;
						}

						else if (buffer[0] == 'n') {
							if (buffer == "newmtl") {
								getline(streamer, buffer);
								matname = buffer;
								materials.emplace(matname, Materials());
								materials.at(matname).freeMaterial();
								materials.at(matname).texture.textureid = -1;
							}
						}

						else if (buffer[0] == 'K') {
							if (buffer == "Kd") {
								vector3 diffusecolor;
								getline(streamer, buffer, ' ');
								diffusecolor.x = stof(buffer);
								getline(streamer, buffer, ' ');
								diffusecolor.y = stof(buffer);
								getline(streamer, buffer, ' ');
								diffusecolor.z = stof(buffer);
								materials.at(matname).color = diffusecolor;
							}
							/*if (buffer == "Ks") {
								getline(streamer, buffer, ' ');
								materials.at(matname).specularexponent = stof(buffer);
							}*/
						}

						else if (buffer[0] == 'm') {
							if (buffer == "map_Kd") {
								getline(streamer, buffer);
								for (int i = 0; i < buffer.size(); i++) {
									if (buffer[i] == '#') {
										buffer.erase(i, std::string::npos);
									}
								}
								Texture text;
								text.loadTexture(buffer);
								materials.at(matname).setTexture(text);
							}
						}
					}
				}
			}
		}
	}
}
void Model::calculateNormals(Vertex* vertices, unsigned int* indices, unsigned int numvertices, unsigned int numindices) {
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
}
void Model::normalizeNormalVertices(Vertex *vertices, int numvertices) {
	for (int i = 0; i < numvertices; i++) {
		vertices[i].normal = (vertices[i].normal).Normalize();
	}
}

Model::Model()
{
}


Model::~Model()
{
}
