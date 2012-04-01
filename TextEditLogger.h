#ifndef TEXTEDITLOGGER_H
#define TEXTEDITLOGGER_H

#include "Logger.h"

#include <QTextEdit>

class TextEditLogger : public Logger
{
	public:
		TextEditLogger( QTextEdit* logger );

		virtual void add_info( const std::wstring& info );
		virtual void add_error( const std::wstring& error );
		virtual void add_warning( const std::wstring& warning );


	private:
		const static QString topText;
		const static QString bottomText;

	private:
		void add_text( const std::wstring& message, QString color );

	private:
		QTextEdit* logger;
		QString outputText;
};

#endif // TEXTEDITLOGGER_H
