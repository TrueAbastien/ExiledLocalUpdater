#pragma once
#include <QFile>
#include <QMap>
#include <QDir>

class SettingFile : public QFile
{
public:
	explicit SettingFile(QString file);
	~SettingFile();

	void setRules(QStringList rules);
	void addRules(QStringList rules);
	void readFile();
	void writeFile();

	void set(QString key, QStringList data);
	void set(QString key, QString data);
	QStringList get(QString key, bool skipEmpty = false) const;

	QString Debug() const;

private:
	QMap<QString, QStringList> content;
	QList<QString> rules;

	QString DataAsString(const QStringList& data) const;
};