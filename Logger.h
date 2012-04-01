#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>

class Logger
{
public:
	typedef std::shared_ptr<Logger> logger_t;

public:
	virtual ~Logger(){}

	virtual void add_info( const std::wstring& info ){}
	virtual void add_error( const std::wstring& info ){}
	virtual void add_warning( const std::wstring& info ){}

	// Получить экземпляр логера.
	static Logger& instance();

	// Установить логер.
	//
	// logger должен быть выделен из вне с использованием delete,
	// и будет удален при смене на новый логер.
	static void set_logger( logger_t logger );

private:
	static logger_t _instance;
};

#endif // LOGGER_H
