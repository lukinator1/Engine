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
void Model::drawModel(Shader &s, Transforming &transform)
{
	for (int i = 0; i < meshes.size(); i++) {
		s.useShader();
		s.updateUniforms(transform.newUnprojectedMatrix(), transform.newTransformationMatrix(), transform.position, materials.at(meshes[i].second));
		meshes[i].first.drawMesh();
	}
}
void Model::setMaterial(Materials &mat) {
	materials.at("") = mat;
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].second = "";
	}
}
void Model::loadModelObj(std::string file) //max size of vector?
{
	std::ifstream fileopener;
	fileopener.open("Rendering/Models/" + file);
	std::vector<Vertex>importedvertices;
	std::vector<vector3>positioncoordinates;
	std::vector<vector2>texturecoordinates;
	std::vector<vector3>normals;
	std::vector<int>positionindices;
	std::vector<int>textureindices;
	std::vector<int>normalindices;
	std::vector<int>indices;
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
				engineLog(__FILE__, __LINE__, "Warning: Model " + file + " did not fully import.", 2, 2, true);
				return; //make an error model
			}

			if (!bigbuffer.empty()) {
				std::stringstream streamer(bigbuffer);
				while (getline(streamer, buffer, ' ') && !comment) {
					if (!buffer.empty()) {

						if (buffer[0] == '#' || buffer[0] == 'o' || buffer[0] == 's') {
							comment = true;
							continue;
						}

						if (buffer[0] == 'f' && buffer.size() == 1) {   //indices
							meshdone = true;
							if (texturecoordinates.size() == 0 && normals.size() == 0) {
								getline(streamer, buffer, ' ');				//x1
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');				//x2
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');				//x3
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);

								if (getline(streamer, buffer, ' ')) {
									while (buffer == "" || buffer == "/t") {
										getline(streamer, buffer, ' ');
									}
									if (buffer.size() >= 1) {
										positionindices.push_back(positionindices[positionindices.size() - 3]);
										positionindices.push_back(positionindices[positionindices.size() - 2]);
										positionindices.push_back(stoi(buffer) - 1);
									}
								}
							}
							else if (texturecoordinates.size() > 0 && normals.size() == 0) {
								getline(streamer, buffer, '/');				//x1
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								textureindices.push_back(stoi(buffer) - 1);

								getline(streamer, buffer, '/');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								textureindices.push_back(stoi(buffer) - 1);


								getline(streamer, buffer, '/');			//x3
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								textureindices.push_back(stoi(buffer) - 1);

								if (getline(streamer, buffer, '/')){
									while (buffer[0] == ' ' || buffer[0] == '/t') {
										buffer.erase(buffer.begin());
									}
									if (buffer.size() >= 1) {
										positionindices.push_back(positionindices[positionindices.size() - 3]);
										positionindices.push_back(positionindices[positionindices.size() - 2]);
										positionindices.push_back(stoi(buffer) - 1);

										getline(streamer, buffer, ' ');
										while (buffer == "" || buffer == "/t") {
											getline(streamer, buffer, ' ');
										}
										textureindices.push_back(textureindices[textureindices.size() - 3]);
										textureindices.push_back(textureindices[textureindices.size() - 2]);
										textureindices.push_back(stoi(buffer) - 1);
									}
								}
							}
							else if (texturecoordinates.size() == 0 && normals.size() > 0) {
								getline(streamer, buffer, '/');				//x1
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/'); 
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normalindices.push_back(stoi(buffer) - 1);

								getline(streamer, buffer, '/');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normalindices.push_back(stoi(buffer) - 1);


								getline(streamer, buffer, '/');			//x3
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normalindices.push_back(stoi(buffer) - 1);

								if (getline(streamer, buffer, '/')) {
									while (buffer[0] == ' ' || buffer[0] == '/t') {
										buffer.erase(buffer.begin());
									}
									if (buffer.size() >= 1) {
										positionindices.push_back(positionindices[positionindices.size() - 3]);
										positionindices.push_back(positionindices[positionindices.size() - 2]);
										positionindices.push_back(stoi(buffer) - 1);

										getline(streamer, buffer, '/');
										getline(streamer, buffer, ' ');
										while (buffer == "" || buffer == "/t") {
											getline(streamer, buffer, ' ');
										}
										normalindices.push_back(normalindices[normalindices.size() - 3]);
										normalindices.push_back(normalindices[normalindices.size() - 2]);
										normalindices.push_back(stoi(buffer) - 1);
									}
								}
							}
							else if (texturecoordinates.size() > 0 && normals.size() > 0) {
								getline(streamer, buffer, '/');				//x1
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								textureindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normalindices.push_back(stoi(buffer) - 1);

								getline(streamer, buffer, '/');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								textureindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normalindices.push_back(stoi(buffer) - 1);


								getline(streamer, buffer, '/');			//x3
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								positionindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, '/');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								textureindices.push_back(stoi(buffer) - 1);
								getline(streamer, buffer, ' ');
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normalindices.push_back(stoi(buffer) - 1);

								if (getline(streamer, buffer, '/')) {
									while (buffer[0] == ' ' || buffer[0] == '/t') {
										buffer.erase(buffer.begin());
									}
									if (buffer.size() >= 1) {
										positionindices.push_back(positionindices[positionindices.size() - 3]);
										positionindices.push_back(positionindices[positionindices.size() - 2]);
										positionindices.push_back(stoi(buffer) - 1);

										getline(streamer, buffer, '/');
										textureindices.push_back(textureindices[textureindices.size() - 3]);
										textureindices.push_back(textureindices[textureindices.size() - 2]);
										textureindices.push_back(stoi(buffer) - 1);

										getline(streamer, buffer, ' ');
										while (buffer == "" || buffer == "/t") {
											getline(streamer, buffer, ' ');
										}
										normalindices.push_back(normalindices[normalindices.size() - 3]);
										normalindices.push_back(normalindices[normalindices.size() - 2]);
										normalindices.push_back(stoi(buffer) - 1);
									}
								}
							}
							continue;
						}

						if (meshdone && positionindices.size() != 0) {
							for (int i = 0; i < positionindices.size(); i++) {
								if (positionindices[i] < 0) {
									positionindices[i] = -positionindices[i];
								}
							}

							for (int i = 0; i < textureindices.size(); i++) {
								if (textureindices[i] < 0) {
									textureindices[i] = -textureindices[i];
								}
							}

							for (int i = 0; i < normalindices.size(); i++) {
								if (normalindices[i] < 0) {
									normalindices[i] = -normalindices[i];
								}
							}

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

						if (buffer[0] == 'm') { //todo: multiple libraries
							if (buffer == "mtllib") {
								getline(streamer, buffer);
								loadMaterials(buffer);
							}
						}

						else if (buffer[0] == 'v' && buffer.size() == 1) {   //vertices
							getline(streamer, buffer, ' ');			//x
							while (buffer == "" || buffer == "/t") {				//eliminate whitespaces
								getline(streamer, buffer, ' ');
							}
							positioncoordinates.push_back(vector3(stof(buffer), 0.0f, 0.0f));

							getline(streamer, buffer, ' ');			//y
							while (buffer == "" || buffer == "/t") {
								getline(streamer, buffer, ' ');
							}
							positioncoordinates.back().y = stof(buffer);


							getline(streamer, buffer, ' ');			//z
							while (buffer == "" || buffer == "/t") {
								getline(streamer, buffer, ' ');
							}
							positioncoordinates.back().z = stof(buffer);
						}

						else if (buffer[0] == 'v' && buffer.size() == 2) {   //texture coordinates
							if (buffer[1] == 't') {
								getline(streamer, buffer, ' ');			//u
								while (buffer == "" || buffer == "/t") {				//eliminate whitespaces
									getline(streamer, buffer, ' ');
								}
								texturecoordinates.push_back(vector2(stof(buffer), 0.0f));

								getline(streamer, buffer, ' ');			//v
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								texturecoordinates.back().y = -stof(buffer);
							}
							if (buffer[1] == 'n') {
								getline(streamer, buffer, ' ');			//x
								while (buffer == "" || buffer == "/t") {				//eliminate whitespaces
									getline(streamer, buffer, ' ');
								}
								normals.push_back(vector3(stof(buffer), 0.0f, 0.0f));

								getline(streamer, buffer, ' ');			//y
								while (buffer == "" || buffer == "/t") {
									getline(streamer, buffer, ' ');
								}
								normals.back().y = stof(buffer);


								getline(streamer, buffer, ' ');			//z
								while (buffer == "" || buffer == "/t") {
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
		engineLog(__FILE__, __LINE__, "Warning: Model " + file + " failed to import. Returned an error model.", 2, 2, true);
		meshes.push_back(std::pair<Mesh, std::string>(Mesh(), ""));
		return; //todo: error model, comments
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
	bool err = false;
	for (int i = 0; i < meshes.size(); i++) {	//check to see if material loaded successfully
		there = false;
		for (auto u = materials.begin(); u != materials.end(); u++) {
			if (meshes[i].second == u->first) {
				there = true;
			}
		}
		if (there == false) {
			meshes[i].second = "";
			err = true;
		}
	}
	if (err) {
		engineLog(__FILE__, __LINE__, "Warning: a material may be missing, error material(s) were used instead.", 2, 2, true);
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
				engineLog(__FILE__, __LINE__, "Warning: Material " + filename + " failed to import. A default error material was returned instead.", 2, 2, true);
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
								materials.at(matname).texture.textureactive = false;
							}
						}

						else if (buffer[0] == 'K') {
							if (buffer == "Kd") {
								vector3 diffusecolor;
								getline(streamer, buffer, ' ');
								while (buffer == "") {
									getline(streamer, buffer, ' ');
								}
								diffusecolor.x = stof(buffer);
								getline(streamer, buffer, ' ');
								while (buffer == "") {
									getline(streamer, buffer, ' ');
								}
								diffusecolor.y = stof(buffer);
								getline(streamer, buffer, ' ');
								while (buffer == "") {
									getline(streamer, buffer, ' ');
								}
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
void Model::calculateNormals(Vertex* vertices, int* indices, int numvertices, int numindices) {
	for (int i = 0; i < numindices; i += 3) {
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];
		vector3 edge1 = vertices[i1].position.Subtract(vertices[i0].position);
		vector3 edge2 = vertices[i2].position.Subtract(vertices[i0].position);
		vector3 normal = edge1.crossProduct(edge2);

		vertices[i0].normal = normal;
		vertices[i1].normal = normal;
		vertices[i2].normal = normal;
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
