#include "LogSaver.h"

LogSaver::LogSaver(const QString& path)
	: QFile(path)
{
	this->open(QFile::ReadWrite | QFile::Text);
}

LogSaver::~LogSaver()
{
	this->close();
}

void LogSaver::WriteText(const QString& text)
{
	this->resize(0);
	QTextStream out(this);
	out << text;
}
