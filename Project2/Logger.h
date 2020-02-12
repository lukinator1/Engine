#pragma once
#include <iostream>
#include <string>
#include <fstream>
class Logger
{
public:
	static std::ofstream EngineLogFile; //configuration file?
	static int engineverbosity;
	static int enginechannel;  //0 = all, 1 = memorymanager, // 2 = rendering, 3 = other/miscellaneous
	static bool showwarnings;

	Logger();
	~Logger();
	void startUp();
	void shutDown();

	//void setVerbosity(int &newverbosity);
	void setEngineLoggerSettings(int newchannel, int newverbosity, bool showwarnings);
	static void engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning); //timestamp
	//void EngineLog(const char* format, ...);
};