#include "Logger.h"
Logger::Logger()
{
}
Logger::~Logger()
{
}
void Logger::startUp()
{
	engineverbosity = 3;
	enginechannel = 0;
	showwarnings = true;
	EngineLogFile.open("EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
	setEngineLoggerSettings(0, 3, true);
}
void Logger::shutDown()
{
	EngineLogFile.close();
}
void Logger::setEngineLoggerSettings(int newchannel, int newverbosity, bool newshowwarnings) { //todo: check if channel/verbosity are in right range
	engineverbosity = newverbosity;
	enginechannel = newchannel;
	showwarnings = newshowwarnings;
}
void Logger::engineLog(std::string file, unsigned int line, std::string errormessage, int verbosity, int channel, bool iswarning)
{
	if (engineverbosity >= verbosity && (enginechannel == channel || enginechannel == 0)) {
		if (iswarning && (showwarnings == true)) {
			std::cout << file << " Line: " << line << " Engine warning!: " << errormessage << std::endl;
			EngineLogFile << file << " Line: " << line << " Engine warning!: " << errormessage << std::endl;
		}
		else {
			std::cout << file << " Line: " << line << " Engine ERROR!: " << errormessage << std::endl;
			EngineLogFile << file << " Line: " << line << " Engine ERROR!: " << errormessage << std::endl;
		}
	}
}
std::ofstream Logger::EngineLogFile("EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
int Logger::engineverbosity = 3;
int Logger::enginechannel = 0;  //0 = all, 1 = memorymanager
bool Logger::showwarnings = true;