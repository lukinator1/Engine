#pragma once
//#include <stdio.h>
//#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
class Logger
{
private: 
	std::ofstream EngineLogFile;
	int engineverbosity = 3;
	int enginechannel = 0;  //0 = all

public:
	Logger();
	~Logger();
	void startUp();
	void shutDown();

	//void setVerbosity(int &newverbosity);
	void setEngineLoggerSettings(int &newverbosity, int &newchannel);
	void VerboseEngineLog(std::string &file, std::string &line, std::string &errormessage, int &verbosity, int &channel);
	//void EngineLog(const char* format, ...);
};

