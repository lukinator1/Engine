#pragma once
#include <map>
#include "Rendering/Materials.h"
#include "Rendering/Mesh.h"
#include "Rendering/Lighting/Lighting.h" 
#include "Physics/Boundingsphere.h"
#include "Entity.h"
class Resourcemanager //todo: error when can't find in map
{
	std::map<std::string, Mesh> meshes;
	std::map<std::string, Materials> materials;
	std::map<std::string, Light> lights;
	std::map<std::string, Directionallight> directionallights;
	std::map<std::string, Pointlight> pointlights;
	std::map<std::string, Spotlight> spotlights;
	std::map<std::string, Boundingsphere> boundingspheres;
	std::map<std::string, Entity> entities;
public:
	void addEntity(Entity &entity, std::string id) {
		entities.emplace(id, entity);
	}
	void deleteEntities (std::string id) {
		for (int i = 0; i < entities.at(id).children.size(); i++) {
			
		}
	}
	Entity getEntity(std::string id) {
		return entities.at(id);
	}
	void addMesh(std::string id, Mesh mesh) {
		meshes.emplace(id, mesh);
	}
	void addMesh(std::string id, std::string Meshfile) {
		meshes.emplace(id, Mesh (Meshfile));
	}
	Mesh &getMesh(std::string id) {
		return meshes.at(id);
	}
	void deleteMesh(std::string id) {
		meshes.at(id).freeMesh();
		meshes.erase(id);
	}
	void addMaterials(std::string id, Materials material) {
		materials.emplace(id, material);
	}
	Materials &getMaterials(std::string id) {
		return materials.at(id);
	}
	void deleteMaterials(std::string id) {
		materials.at(id).freeMaterial();
		materials.erase(id);
	}
	/*void addLight(std::string id, Light light) {
		lights.emplace(id, light);
	}
	Light getLight(std::string id) {
		return lights.at(id);
	}
	void deleteLight(std::string id) {
		lights.at(id).freeLight();
		lights.erase(id);
	}*/
	void addDirectionalLight(std::string id, Directionallight dlight) {
		directionallights.emplace(id, dlight);
	}
	Directionallight &getDirectionalLight(std::string id) {
		return directionallights.at(id);
	}
	void deleteDirectionalLight(std::string id) {
		/*lights.at(id).freeLight();*/
		directionallights.erase(id);
	}
	void addPointLight(std::string id, Pointlight plight) {
		pointlights.emplace(id, plight);
	}
	Pointlight &getPointLight(std::string id) {
		return pointlights.at(id);
	}
	void deletePointLight(std::string id) {
		/*lights.at(id).freeLight();*/
		pointlights.erase(id);
	}
	void addSpotLight(std::string id, Spotlight slight) {
		spotlights.emplace(id, slight);
	}
	Spotlight &getSpotLight(std::string id) {
		return spotlights.at(id);
	}
	void deleteSpotLight(std::string id) {
		/*lights.at(id).freeLight();*/
		spotlights.erase(id);
	}
	void addBoundingSphere(std::string id, Boundingsphere bsphere) {
		boundingspheres.emplace(id, bsphere);
	}
	Boundingsphere &getBoundingSphere(std::string id) {
		return boundingspheres.at(id);
	}
	void deleteBoundingSpheres(std::string id) {
		/*lights.at(id).freeLight();*/
		boundingspheres.erase(id);
	}

	Resourcemanager();
	~Resourcemanager();
};

