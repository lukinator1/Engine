#include "FileHandler.h"
FileHandler::FileHandler()
{
}
FileHandler::~FileHandler()
{
}
void FileHandler::startUp() {

}
void FileHandler::shutDown() {

}
void FileHandler::writeToFile(std::string &filename, std::string &buffer) {
	std::ofstream filetobewritten;
	filetobewritten.open(filename);
	filetobewritten << buffer << std::endl;
}
