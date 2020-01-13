#include "Logger.h"



Logger::Logger()
{
}


Logger::~Logger()
{
}


//void Logger::EngineLog(const char* format, ...) {
//}
void Logger::setVerbosity(int &newverbosity) {
	engineverbosity = newverbosity;
}
void Logger::VerboseEngineLog(int &verbosity, std::string & file, std::string & line, std::string & errormessage)
{
	if (engineverbosity >= verbosity) {
		std::cout << "ERROR!: " << errormessage << file << ": line " << line << ".";
	}
}
