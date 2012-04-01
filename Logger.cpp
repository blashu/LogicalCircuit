#include "Logger.h"

Logger::logger_t Logger::_instance = Logger::logger_t();

Logger& Logger::instance()
{
	return *_instance;
}

void Logger::set_logger( Logger::logger_t logger )
{
	_instance = logger;
}
