#pragma once
#include <string>
#include <fstream>
class Modelloader
{
public:
	Modelloader();
	~Modelloader();
	void loadMeshObj(std::string file);
};

