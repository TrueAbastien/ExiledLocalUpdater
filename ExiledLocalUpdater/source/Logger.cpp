#include "Logger.h"
#include <QTime>


Logger* Logger::instance = nullptr;

Logger::Logger(QTextEdit* widget)
	: edit(widget)
{
	if (edit != nullptr)
	{
		edit->setTextColor(QColor(128, 128, 128));
		edit->insertPlainText(">> Session opened at " + QTime::currentTime().toString("HH:mm:ss ap") + ":");
	}
}

void Logger::Print(const QString& str)
{
	__displayWithColor("-- " + str, QColor(0, 0, 0));
}

void Logger::Info(const QString& str)
{
	__displayWithColor("- " + str, QColor(33, 124, 204));
}

void Logger::Warn(const QString& str)
{
	__displayWithColor("/!\\ " + str, QColor(181, 145, 54));
}

void Logger::Success(const QString& str)
{
	__displayWithColor(str, QColor(49, 181, 60));
}

void Logger::Failed(const QString& str)
{
	__displayWithColor(str, QColor(214, 51, 79));
}

void Logger::Debug(const QString& str)
{
#ifdef _DEBUG
	__displayWithColor(">> " + str, QColor(237, 116, 235));
#endif
}

void Logger::__displayWithColor(const QString& msg, const QColor& col)
{
	if (edit != nullptr)
	{
		edit->setTextColor(col);
		edit->insertPlainText("\n " + msg);
	}
}
