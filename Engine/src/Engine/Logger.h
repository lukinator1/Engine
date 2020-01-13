#pragma once
//#include <stdio.h>
//#include <Windows.h>
#include <iostream>
#include <string>
class Logger
{
private: 
	int engineverbosity = 3;
public:
	Logger();
	~Logger();
	void setVerbosity(int &newverbosity);
	void VerboseEngineLog(int &verbosity, std::string &file, std::string &line, std::string &errormessage);
	//void EngineLog(const char* format, ...);
};

