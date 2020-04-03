#include "Model.h"
#include "Shader.h"
void Model::freeModel()
{
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].freeMesh();
	}
	for (int i = 0; i < materials.size(); i++) {
		materials[i].freeMaterial();
	}
	meshes.clear();
	materials.clear();
}
Model::Model(std::string file)
{
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
	int i = 0;

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
					if (!buffer.empty()) {
						if (buffer[0] == '#') {
							continue;
						}

						else if (buffer[0] == 'v' && buffer.size() == 1) {   //vertices
							if (meshdone && positionindices.size() != 0) {
								for (int i = 0; i < positionindices.size(); i++) {	//mesh ready to load
									importedvertices.push_back(Vertex(vector3(positioncoordinates[positionindices[i]])));
									importedvertices.back().texture = texturecoordinates[textureindices[i]];
									importedvertices.back().normal = normals[normalindices[i]];
									indices.push_back(i);
								}
								meshes.push_back(Mesh());
								meshes[i].makeMesh(&importedvertices[0], &indices[0], importedvertices.size(), indices.size());
								importedvertices.clear();
								indices.clear();
								meshdone = false;
								i++;
							}
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
								texturecoordinates.back().y = stof(buffer);
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

						else if (buffer[0] == 'f' && buffer.size() == 1) {   //indices
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
}


Model::Model()
{
}


Model::~Model()
{
}
