#pragma once
#include <QObject>
#include <QTextEdit>

class Logger : public QObject
{
	Q_OBJECT

public:

	void Print(const QString& str);
	void Info(const QString& str);
	void Warn(const QString& str);
	void Success(const QString& str);
	void Failed(const QString& str);

	void Debug(const QString& str);

	static Logger* get(QTextEdit* widget = nullptr)
	{
		if (widget != nullptr && instance == nullptr)
			instance = new Logger(widget);
		return instance;
	}

private:
	static Logger* instance;
	Logger(QTextEdit* widget);

	QTextEdit* edit;
	void __displayWithColor(const QString& msg, const QColor& col);
};