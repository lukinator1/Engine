#pragma once
#include <iostream>
#include <string>
#include <fstream>
class Logger
{
private:
	std::ofstream EngineLogFile; //configuration file?
	int engineverbosity;
	int enginechannel;  //0 = all, 1 = memorymanager
	bool showwarnings;

public:
	Logger();
	~Logger();
	void startUp();
	void shutDown();

	//void setVerbosity(int &newverbosity);
	void setEngineLoggerSettings(int newchannel, int newverbosity, bool showwarnings);
	void engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning); //timestamp
	//void EngineLog(const char* format, ...);
};