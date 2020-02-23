#include "Logger.h"
Logger::Logger()
{
}
Logger::~Logger()
{
}
void Logger::startUp(int * channels, int verbosity, bool warn)
{
	engineverbosity = verbosity;
		for (int i = 0; i < 4; i++) {
			enginechannels[i] = channels[i];
		}
	showwarnings = warn;
	if (clear = true) {
		EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
	}
	else {
		EngineLogFile.open("Enginelogs/EngineLog.txt", std::ofstream::out);
	}
}
void Logger::shutDown()
{
	EngineLogFile.close();
}
void Logger::setEngineLoggerSettings(int mem, int render, int misc, int newverbosity, bool newshowwarnings) { 
	engineverbosity = newverbosity;
	enginechannels[0] = mem;
	enginechannels[1] = render;
	enginechannels[2] = misc;
	showwarnings = newshowwarnings;
}
void Logger::engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning)
{
	if (engineverbosity >= verbosity && ( ((enginechannels[0] == 1) && channel == 1) || ((enginechannels[1] == 1) && channel == 2) || ((enginechannels[2] == 1) && channel == 3) || (channel == 0))) {
		if (iswarning && (showwarnings == true)) {
			std::cout << file << std::endl << " Line: " << line << std::endl << "Engine warning!: " << errormessage << std::endl;
			EngineLogFile << file << std::endl <<  " Line: " << line << std::endl <<"Engine warning!: " << errormessage << std::endl;
		}
		else {
			std::cout << file << std::endl << " Line: " << line << std::endl << "Engine ERROR!: " << errormessage << std::endl;
			EngineLogFile << file << std::endl << " Line: " << line << std::endl << "Engine ERROR!: " << errormessage << std::endl;
		}
	}
}
std::ofstream Logger::EngineLogFile("Enginelogs/EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
int Logger::engineverbosity = 3;
int Logger::enginechannels[3];  //0 = all, 1 = memorymanager
bool Logger::showwarnings = true;