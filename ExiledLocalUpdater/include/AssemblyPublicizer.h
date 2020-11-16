#pragma once
#include <QObject>
#include <QProcess>
#include <QFile>
#include <QDir>

class AssemblyPublicizer : public QObject
{
	Q_OBJECT

public:
	AssemblyPublicizer();
	QString Publicize(const QString& filePath, const QString& file, const QString& execPath) const;
	QString Bring(const QString& filePath, const QString& file, const QString& targetPath) const;

private:
	//
};