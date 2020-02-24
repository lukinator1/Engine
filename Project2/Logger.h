#pragma once
#include <iostream>
#include <string>
#include <fstream>
class Logger
{
public:
	/*enum Channels {
		Memorymanager,
		Rendering,
		Miscellaneous
	};*/
	static std::ofstream EngineLogFile; //configuration file?
	static unsigned int engineverbosity;
	static unsigned int enginechannels[3];  //0 = all, 1 = memorymanager, // 2 = rendering, 3 = other/miscellaneous 
	static bool showwarnings;
	static bool clear;
	static bool haltlogs;
	Logger();
	~Logger();
	static void startUp();
	static void clearLogs();
	void shutDown();

	//void setVerbosity(int &newverbosity);
	static void setEngineLoggerSettings(unsigned int mem, unsigned int render, unsigned int misc, unsigned int newverbosity, bool newshowwarnings);
	static void engineLog(std::string file, unsigned int line, std::string errormessage, unsigned int verbosity, unsigned int channel, bool iswarning); //timestamp
	//void EngineLog(const char* format, ...);
};