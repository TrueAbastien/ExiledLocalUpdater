#include "SettingFile.h"

#include <QTextStream>
#include <sstream>


SettingFile::SettingFile(QString file)
	: QFile("settings/" + file + ".settings")
{
	this->open(QFile::ReadWrite | QFile::Text | QFile::ExistingOnly);
}

SettingFile::~SettingFile()
{
	this->close();
}

void SettingFile::setRules(QStringList _rules)
{
	rules.clear();
	addRules(_rules);
}

void SettingFile::addRules(QStringList _rules)
{
	for (QString& rule : _rules)
	{
		if (rule.contains("$"))
			rules.append(rule.replace("$", ""));
		else rules.append(rule);
	}
}

void SettingFile::readFile()
{
	std::string line, value;
	QTextStream in(this);
	while (!in.atEnd())
	{
		line = in.readLine().toStdString();

		for (QString rule : rules)
		{
			if (line.find(rule.toStdString() + "=") == 0)
			{
				if (line.size() == (rule.size() + size_t(1)))
				{
					this->set(rule, "");
				}
				else
				{
					QString qLine = QString::fromStdString(line);
					this->set(rule, qLine.right(qLine.size() - qLine.indexOf("=") - 1).remove("\n").split(','));
				}
			}
		}
	}
}

void SettingFile::writeFile()
{
	this->resize(0);
	QTextStream out(this);
	for (QString rule : rules)
	{
		out << rule << "=" << DataAsString(content[rule]) << '\n';
	}
}

void SettingFile::set(QString key, QStringList data)
{
	data.removeAll("");
	this->content[key] = data;
}

void SettingFile::set(QString key, QString data)
{
	this->content[key] = QStringList{ data };
}

QStringList SettingFile::get(QString key, bool skipEmpty) const
{
	if (skipEmpty)
	{
		QStringList data = this->content[key];
		data.removeAll("");
		return data;
	}
	return this->content[key];
}

QString SettingFile::DataAsString(const QStringList& data) const
{
	QString res = "";
	foreach(QString ele, data)
		res += ele + ",";
	return res.left(res.size() - 1);
}

QString SettingFile::Debug() const
{
	QString res = "";
	foreach(QString key, content.keys())
	{
		res += key + "->" + DataAsString(content[key]) + '\n';
	}
	return res;
}