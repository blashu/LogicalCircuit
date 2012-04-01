#include "TextEditLogger.h"

#include <QtGui>

const QString TextEditLogger::topText = "<html><head></head><body>";
const QString TextEditLogger::bottomText = "</body></html>";

TextEditLogger::TextEditLogger( QTextEdit* logger )
{
	this->logger = logger;
	outputText = topText + bottomText;

	//QStyleSheetItem * styleSheetItem = new QStyleSheetItem(  );
	logger->document()->setDefaultStyleSheet( "p {margin-top:5px;margin-bottom:5px;} " );
}

void TextEditLogger::add_info( const std::wstring& info )
{
	add_text( info, "#000" );
}

void TextEditLogger::add_error( const std::wstring& error )
{
	add_text( error, "#B40404" );
}

void TextEditLogger::add_warning( const std::wstring& warning )
{
	add_text( warning, "#868A08" );
}

void TextEditLogger::add_text( const std::wstring& message, QString color )
{
	outputText.remove( outputText.size() - bottomText.size() - 1,
										 bottomText.size() );

	outputText += "<p>[" + QTime::currentTime().toString() + "] " + "<font color=" + color + ">" +
									 QString::fromStdWString( message ).replace("&","&amp;").replace(">","&gt;").replace("<","&lt;") +
								"</font></p>" + bottomText;

	logger->setHtml( outputText );
	logger->verticalScrollBar()->setValue( logger->verticalScrollBar()->maximum() );
}
