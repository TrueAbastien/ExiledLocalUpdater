#pragma once
#include <QFile>
#include <QTextStream>

class LogSaver : public QFile
{
public:
	explicit LogSaver(const QString& path = "logs.txt");
	~LogSaver();

	void WriteText(const QString& text);
};