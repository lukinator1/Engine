#pragma once
#include <fstream>
#include <string>
class FileHandler
{
public:
	FileHandler();
	~FileHandler();
	void shutDown();
	void writeToFile(std::string &filename, std::string &buffer);
	void startUp();
};

