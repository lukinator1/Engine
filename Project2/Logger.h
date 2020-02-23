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
	static int engineverbosity;
	/*static int enginechannel;*/
	static int enginechannels[3];  //0 = all, 1 = memorymanager, // 2 = rendering, 3 = other/miscellaneous
	static bool showwarnings;
	bool clear = false;

	Logger();
	~Logger();
	void startUp(int * channeler, int verbosity, bool warn);
	void shutDown();

	//void setVerbosity(int &newverbosity);
	void setEngineLoggerSettings(int mem, int render, int misc, int newverbosity, bool newshowwarnings);
	static void engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning); //timestamp
	//void EngineLog(const char* format, ...);
};