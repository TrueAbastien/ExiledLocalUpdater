#pragma once
#include <QCache>
#include <QDir>
#include <QMainWindow>

class ThemeCache : public QCache<QString, QString>
{
public:
	ThemeCache(QString dir = QString(""));
	void LoadAt(QString dir);

	QStringList AllStyleSheets() const;
	void Set(QWidget* wdg, QString styleName);

	QString Get() const;

private:
	QDir stylesheetDirectory;
	QStringList allStyleSheets;
	QString current = "";
};