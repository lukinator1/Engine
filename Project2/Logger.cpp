#include "Logger.h"
Logger::Logger()
{
}
Logger::~Logger()
{
}
void Logger::startUp()
{
	EngineLogFile.open("EngineLog.txt", std::ofstream::out | std::ofstream::trunc);
	setEngineLoggerSettings(0, 3, true);
}
void Logger::shutDown()
{
	EngineLogFile.close();
}
//void Logger::EngineLog(const char* format, ...) {
//}
void Logger::setEngineLoggerSettings(int newchannel, int newverbosity, bool newshowwarnings) { //todo: check if channel/verbosity are in right range
	engineverbosity = newverbosity;
	enginechannel = newchannel;
	showwarnings = newshowwarnings;
}
void Logger::engineLog(std::string & file, std::string & line, std::string & errormessage, int &verbosity, int &channel, bool iswarning)
{
	if (engineverbosity >= verbosity && (enginechannel == channel || enginechannel == 0)) {
		if (iswarning && (showwarnings == true)) {
			std::cout << "Engine warning: " << errormessage << ", " << file << " : line " << line << "." << std::endl;
			EngineLogFile << "Engine warning!: " << errormessage << ", " << file << ": line " << line << "." << std::endl;
		}
		else {
			std::cout << "Engine ERROR!: " << errormessage << ", " << file << " : line " << line << "." << std::endl;
			EngineLogFile << "Engine ERROR!: " << errormessage << ", " << file << ": line " << line << "." << std::endl;
		}
	}
}
