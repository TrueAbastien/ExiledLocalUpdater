#pragma once
#include <QObject>
#include <QProcess>
#include <QDir>

class ArchiveExtractor : public QObject
{
	Q_OBJECT

public:
	ArchiveExtractor();
	void Open(const QString& archiveFullPath, bool removeCopy = true);
	//

private:
	//
};